#pragma once

//#include "gdevice.h" // the library ?

#define DEBUG_SHOW_GLSL_SOURCE	

#include "os/platform.h"
#include "os/application.h"
#include "os/keyboard.h"

#include "type/gpu.h"
#include "type/node.h"
#include "type/node2.h"
#include "type/terrain/heightmap.h"

#include "application/assets/worlds/planet1/parameters.h"

class Walker : gd::Application<Walker>
{
    // TODO ECS based entity creation, with components and systems

    // POV
    // NOTE This is indeed used to move and rotate the scene.
    // As a matter of fact, there is no camera here and the real POV 
    // is always the origin and pointing north.
    dmat3 camera; 
    double speedFactor;

    // Scene
    Node scene;
	// TODO auto heightmap = scene.add<Heightmap>();
    Heightmap heightmap; //gd::Asset<Heightmap>
    // NOTE any GPU asset should have a memory handler, 
    // possibly nested into a ECS design pattern.
    // TODO Set update function

    // Time and Diffuse light direction
    float time; 
    Light sun;  // TODO vec3 sun; 

    

	
public:

	void onOpen(Window<Walker>& window)
    {
        heightmap.setTileResolution(TILE_RESOLUTION);
	    heightmap.setLODs(CLIPMAPS_COUNT);	
	    heightmap.light = &sun;

        scene.transform.rotation = vec3(-90, 0, 0);
	    scene.children.push(&heightmap);

        speedFactor = 40;
	    camera.position = dvec3(0,0,10.0);
	    camera.rotation = dvec3(0,0,0);
    	
        time = TIME_START;
        sun.id = 0;
	    sun.spot_direction = rotate((time-7)*360/24, 0.7f, 1.7f) * vec3(0.1,-0.8,0.1); 

        // TODO add InputControl
    }

	void onSize(Window<Walker>& window)
    {
	    window.renderer->setViewport(window.size); 
	    window.renderer->setProjection(FOV, NEAR_CLIP_PLANE, heightmap.visibility());
    }

	void onDraw(Window<Walker>& window, double elapsed)
    {
        Renderer& renderer = *window.renderer;
	    
        ///////////////////////////////
        // Update scene by user input.
        //

        // TODO
        // camera = transform(camera, window, ROTATION_SPEED);

	        // Camera rotation
	        dvec3 mouse_rotation     = dvec3(window.mouseDeltaY(), 0, window.mouseDeltaX());
            dvec3 cursors_rotation   = dvec3(Key::cursorDeltaY(), 0, Key::cursorDeltaX()); // TODO window.HasFocus()
	        dvec3 input_rotation     = double(!window.isPointerVisible) * mouse_rotation + 0.01 * cursors_rotation;
	        camera.rotation   -= ROTATION_SPEED * input_rotation;		// counter-clockwise
	        camera.rotation.z  = mod(camera.rotation.z, 360.0);			// positive horizontal axis
	        camera.rotation.x  = clamp(camera.rotation.x, -90.0, +90.0);// clamped to [-90,+90] in order to avoid gimbal lock

            // Camera position
	        dmat3 T = transpose(rotate(camera.rotation));
	        dvec3 forward =  T.yAxis;
	        dvec3 strafe  = -T.xAxis;
	        double factor = (Key(LSHIFT).isPressed() ? BOOST_FACTOR : 1) * (Key(LCONTROL).isPressed() ? WARP_FACTOR : 1) * pow(speedFactor, 2.0);
	        double speed = factor * TRANSLATION_SPEED;
	        camera.position += forward*(Key('W').isPressed()? +speed : Key('S').isPressed()? -speed : 0) + strafe*(Key('A').isPressed()? +speed : Key('D').isPressed()? -speed : 0);
	        camera.position.z += (Key(' ').isPressed()? +speed : Key('Z').isPressed()? -speed : 0); // TODO could be included into strafe



        /////////////////////////////
        // Update time by user input

        // TODO
        // time = 

	    // Time
	    float timeSpeed = (Key('E').isPressed() ? +1 : Key('R').isPressed() ? -1 : 0) * float(TIME_SPEED) * (speedFactor);
	    time = fmod( time + timeSpeed*float(elapsed), 24.0f );
	    sun.spot_direction = rotate((time-7)*360.0f/24.0f, 40.0f, 0.0f) * vec3(0.2, -0.8, 0.1);

	    // TODO: Resolve this dependency.
	    for(int i=0; i<Controls::CONTROLCOUNT; i++)
        {
		    Key(Controls::Bindings[i]).isPressed();
	    }



        ////////////////////////////
        // Update scene
        //
        double level = heightmap.moveAt(camera); // moves and rotates the world (not the camera)
        heightmap.generateInvalidatedTiles(renderer);

        // TODO: Sleep while compute shader is working.
/*      double amountSleep = 1.0/TARGET_FPS - elapsed;
        DEBUG_TRACE(amountSleep);
        if( amountSleep>0 ) {
            Sleep( amountSleep ); 
        }*/

        

	    ////////////////////////////
	    // Rendering
	    //
        // TODO: renderer.barrier 
	    renderer.setFogDensity(FOG_DENSITY); // TODO: Move to world properties.
	    renderer.clear();
	    renderer.inverseRotationMatrix = transpose(RotationMatrix(scene.transform.rotation) * RotationMatrix(heightmap.transform.rotation));
        // TODO: renderer.setTarget<rgba>( NULL );
	    renderer.draw( scene );
	    renderer.drawSky();


	    // 
	    // Misc controls
	    //
	    speedFactor = clamp(speedFactor + window.mouseDeltaWheel()/200.0, 0.05, 31.6228);
	    if(Key(ESCAPE).isJustPressed()) window.togglePointer();
        if(Key('L').isJustPressed()) window.toogleFullscreen();
	    if(Key('X').isPressed()) window.close();

        //
        // Show rendering state
        //
	    char controls_string[255];
	    renderer.controls.getString(controls_string);

	    static Timer fpsTimer;
	    static dvec3 previous_pos; 
	    static int counter = 0;
	    static float interval;
	    if((++counter) % FPS_FREQUENCY == 0) 
            interval = fpsTimer.elapsed()/FPS_FREQUENCY;
	    int fps = (int)(1.0/interval);

		char camera_position[256];
		STR(METERS_PER_TILE * camera.position, camera_position);

		char camera_rotation[256];
		STR(camera.rotation, camera_rotation);

        // TODO FPS=%i%s CPU=%i%s GPU=%i%s
	    window.setTitle("FPS=%i%s Debug=[%s] Speed=%.2fkmh (x%i) Time=%02i.%02i Location=(%s) Direction=(%s)", 
		    fps, fps<100 ? "  " : "",
            controls_string, 
		    distance(camera.position, previous_pos) * METERS_PER_TILE*100/interval * 3600/1000,
		    int(speedFactor),
		    int(time), int(fract(time)*60),
		    camera_position,
			camera_rotation
	    );
	    previous_pos = camera.position;

        DEBUG_TRACE_ONCE(renderer.vertices);
    }

    int run() {
        return window.runPlainMessageLoop();
    }

private:
// TODO make private static functions for
// - Updating the scene by using the user input
// - Rendering the scene
// - Display debug stuff
// TODO make these functions tasks that can run in CPU or GPU as system functions over components.


};



int main()
{
    return Walker().run();
}
