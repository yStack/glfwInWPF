using System.Runtime.InteropServices;

namespace WpfApp.View
{
    public class RenderEngine
    {
        [DllImport("glhost.dll", EntryPoint = "open_window", CharSet = CharSet.Unicode)]
        internal static extern int BuildWindow(int parent, int width, int height, bool visible = false);
    }

}
