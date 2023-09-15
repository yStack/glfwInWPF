using System;
using System.Runtime.InteropServices;
using System.Windows.Controls;
using System.Windows.Interop;

namespace WpfApp.View
{
    internal class RenderHost : HwndHost
    {
        private readonly Border _parent;

        public RenderHost(Border parent)
        {
            _parent = parent;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            int width = (int)_parent.ActualWidth;
            int height = (int)_parent.ActualHeight;
            int num = RenderEngine.BuildWindow(hwndParent.Handle.ToInt32(), width, height);
            if (num != 0)
            {
                return new HandleRef(this, new IntPtr(num));
            }
            return new HandleRef(this, IntPtr.Zero);
        }


        protected override void DestroyWindowCore(HandleRef hwnd)
        {

        }
    }

}
