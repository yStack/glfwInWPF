using System.Windows;
using System.Windows.Controls;
using WpfApp.View;

namespace WpfApp.View
{
    /// <summary>
    /// gRender.xaml 的交互逻辑
    /// </summary>
    public partial class RenderControl : UserControl
    {
        public RenderControl()
        {
            InitializeComponent();
        }


        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            if(hostBorder.IsVisible)
            {
                if (hostBorder.Child == null)
                {
                    //创建一个child附加到host中
                    RenderHost child = new RenderHost(hostBorder);
                    hostBorder.Child = child;
                }
            }
        }
    }
}
