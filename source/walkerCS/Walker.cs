using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;
using GDevice;


namespace walkerCS
{
    class Walker
    {
        static void Main(string[] args)
        {
            int x = GDevice.Window.Create();
            Console.WriteLine("HEllo: " + x.ToString());
        }

    }
}
