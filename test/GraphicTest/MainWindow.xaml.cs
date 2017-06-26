using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using GraphicLibWrapper;

namespace GraphicTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        ImageSource CreateBitmap(Byte[] data, int width, int height)
        {
            UInt32[] bmp = new UInt32[width * height];
            Buffer.BlockCopy(data, 0, bmp, 0, width * height * sizeof(UInt32));

            return BitmapSource.Create(width, height, 96, 96, PixelFormats.Bgr32, null, bmp, width * sizeof(UInt32));
        }

        private void m_btnTest_Click(object sender, RoutedEventArgs e)
        {
            Byte[] bmpData = GraphicLib.DoATest();

            m_image.Source = CreateBitmap(bmpData, 500, 500);   // HARD CODED!
        }

    }
}
