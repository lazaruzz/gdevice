using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;


namespace walkerCS
{
    class Walker
    {
        [DllImport("gdevice.dll")]
        public static extern int gdCreateWindow();

        static void Main(string[] args)
        {
            int x = gdCreateWindow(); 
            Console.WriteLine("HEllo: " + x.ToString());
        }
    }
}
