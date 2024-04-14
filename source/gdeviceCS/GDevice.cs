using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;

namespace GDevice
{
    public class Window
    {
        [DllImport("gdevice.dll", EntryPoint = "gdCreateWindow")]
        public static extern int Create();
    }
}
