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
using System.IO;
using System.Windows.Forms;

namespace DataConverterGadget
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<string> m_validExtensions;

        public MainWindow()
        {
            InitializeComponent();

            m_validExtensions = new List<string>() { ".gif", ".tif", ".jpg", ".png", ".bmp", ".ico" };
        }

        private void CreateImageHeaderFile(string pathSrc, string dirDestination)
        {
            // Create bitmap
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.UriSource = new Uri(pathSrc, UriKind.RelativeOrAbsolute);
            bitmap.EndInit();

            BitmapSource bmp = new FormatConvertedBitmap(bitmap, PixelFormats.Bgra32, null, 0);

            StreamWriter sWriter = null;
            try
            {
                string nameOG = Path.GetFileNameWithoutExtension(pathSrc);
                string filename = System.Text.RegularExpressions.Regex.Replace(nameOG, @"\s+", "_");
                filename = System.Text.RegularExpressions.Regex.Replace(filename, @"-", "_");
                string filepath = Path.Combine(dirDestination, filename + ".h");
                int pixWidth = bmp.PixelWidth;
                int pixHeight = bmp.PixelHeight;
                byte[] pixelData = new byte[pixWidth * pixHeight * 4];
                bmp.CopyPixels(pixelData, pixWidth * 4, 0);

                using (sWriter = new StreamWriter(filepath))
                {
                    string lbdefine = "_" + filename.ToUpper() + "_H";
                    sWriter.WriteLine("#ifndef " + lbdefine);
                    sWriter.WriteLine("#define " + lbdefine);
                    sWriter.WriteLine("");

					sWriter.WriteLine("#include <stdint.h>");
					sWriter.WriteLine("");

					// create variable for image height
					sWriter.WriteLine("#define " + filename.ToUpper() + "_HEIGHT       " + pixHeight.ToString());
                    // create variable for image width
                    sWriter.WriteLine("#define " + filename.ToUpper() + "_WIDTH        " + pixWidth.ToString());


                    // declare data array variable
                    string varType = "extern uint32_t ";
                    sWriter.WriteLine(varType + filename + "_data [" + (pixelData.Length/4)+ "];");

                    //for (int i = 0; i < pixelData.Length; i += 4)
                    //{
                    //    byte b = pixelData[i];
                    //    byte g = pixelData[i + 1];
                    //    byte r = pixelData[i + 2];
                    //    byte a = pixelData[i + 3];

                    //    sWriter.WriteLine(String.Format("0x{0}{1}{2},", r.ToString("X2"), g.ToString("X2"), b.ToString("X2"), a.ToString("X2")));
                    //}

                    //// close data array
                    //sWriter.WriteLine("};");

                    sWriter.WriteLine("");
                    sWriter.WriteLine("#endif        // #define " + lbdefine);
                }
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Oops", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            finally
            {
                if (sWriter != null) { sWriter.Close(); }
            }
        }
        private void CreateImageCFile(string pathSrc, string dirDestination)
        {
            // Create bitmap
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.UriSource = new Uri(pathSrc, UriKind.RelativeOrAbsolute);
            bitmap.EndInit();

            BitmapSource bmp = new FormatConvertedBitmap(bitmap, PixelFormats.Bgra32, null, 0);

            StreamWriter sWriter = null;
            try
            {
                string nameOG = Path.GetFileNameWithoutExtension(pathSrc);
                string filename = System.Text.RegularExpressions.Regex.Replace(nameOG, @"\s+", "_");
                filename = System.Text.RegularExpressions.Regex.Replace(filename, @"-", "_");
                string filepath = Path.Combine(dirDestination, filename + ".cpp");
                int pixWidth = bmp.PixelWidth;
                int pixHeight = bmp.PixelHeight;
                byte[] pixelData = new byte[pixWidth * pixHeight * 4];
                bmp.CopyPixels(pixelData, pixWidth * 4, 0);

                using (sWriter = new StreamWriter(filepath))
                {
					sWriter.WriteLine("#include <stdint.h>");
					sWriter.WriteLine("");

					string varType = "uint32_t ";
                    // create data array variable
                    sWriter.WriteLine(varType + filename + "_data [] = {");

                    for (int i = 0; i < pixelData.Length; i += 4)
                    {
                        byte b = pixelData[i];
                        byte g = pixelData[i + 1];
                        byte r = pixelData[i + 2];
                        byte a = pixelData[i + 3];

                        sWriter.WriteLine(String.Format("0x{0}{1}{2}{3},", a.ToString("X2"), r.ToString("X2"), g.ToString("X2"), b.ToString("X2")));
                    }

                    // close data array
                    sWriter.WriteLine("};");
                }
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Oops", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            finally
            {
                if (sWriter != null) { sWriter.Close(); }
            }
        }

        private string GetDirectory()
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowDialog();
            string path = "";
            if (Directory.Exists(fbd.SelectedPath))
                path = fbd.SelectedPath;

            return path;
        }
        private string GetFile()
        {
            string file = "";
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.CheckFileExists = true;
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                file = ofd.FileName;
            }

            return file;
        }

        private void m_btnSrcBrowse_Click(object sender, RoutedEventArgs e)
        {
            m_tbSrcPath.Text = GetDirectory();
        }

        private void m_btnDestinationBrowse_Click(object sender, RoutedEventArgs e)
        {
            m_tbDestinationPath.Text = GetDirectory();
        }

        private void m_btnImgBrowse_Click(object sender, RoutedEventArgs e)
        {
            m_tbImgPath.Text = GetFile();
        }

        private void m_btnConvert_Click(object sender, RoutedEventArgs e)
        {
            Directory.CreateDirectory(m_tbDestinationPath.Text);           
            if (Directory.Exists(m_tbSrcPath.Text) && Directory.Exists(m_tbDestinationPath.Text))
            {
                string[] files = Directory.GetFiles(m_tbSrcPath.Text, "*.*", SearchOption.AllDirectories);
                List<string> valid = new List<string>();
                foreach (string file in files)
                {
                    if (m_validExtensions.Contains(Path.GetExtension(file)))
                        valid.Add(file);
                }

                m_tbDone.Visibility = Visibility.Collapsed;
                m_btnConvert.Visibility = Visibility.Collapsed;

                foreach (string file in valid)
                {
                    CreateImageHeaderFile(file, m_tbDestinationPath.Text);
                    CreateImageCFile(file, m_tbDestinationPath.Text);
                }

                m_btnConvert.Visibility = Visibility.Visible;
                m_tbDone.Visibility = Visibility.Visible;
            }

            System.Windows.MessageBox.Show("Done");
        }

        private void m_btnDazzle_Click(object sender, RoutedEventArgs e)
        {
            if (File.Exists(m_tbImgPath.Text))
            {
				if (m_validExtensions.Contains(Path.GetExtension(m_tbImgPath.Text)))
				{
					// Create bitmap
					BitmapImage bitmap = new BitmapImage();
					bitmap.BeginInit();
					bitmap.UriSource = new Uri(m_tbImgPath.Text, UriKind.RelativeOrAbsolute);
					bitmap.EndInit();

					BitmapSource bmp = new FormatConvertedBitmap(bitmap, PixelFormats.Bgra32, null, 0);

					try
					{
						int pixWidth = bmp.PixelWidth;
						int pixHeight = bmp.PixelHeight;
						byte[] pixelData = new byte[pixWidth * pixHeight * 4];
						bmp.CopyPixels(pixelData, pixWidth * 4, 0);

						for (int i = 0; i < pixHeight; i++)
						{
							bool change = i % 10 == 0;

							for (int j = 0; j < pixWidth; j++)
							{
								change = change || i % 10 == 0;

								if (change)
								{
									int indx = Math.Min(((i * pixWidth) + j) * 4, pixelData.Length);
									pixelData[indx] = 255;
									pixelData[indx + 1] = 255;
									pixelData[indx + 2] = 255;
									pixelData[indx + 3] = 255;
								}
							}
						}

						int stride = pixWidth * (PixelFormats.Bgra32.BitsPerPixel / 8);
						bmp = BitmapSource.Create(pixWidth, pixHeight, 96, 96, PixelFormats.Bgra32, null, pixelData, stride);
					}
					catch (Exception ex)
					{
						System.Windows.MessageBox.Show(ex.Message, "Oops", MessageBoxButton.OK, MessageBoxImage.Error);
					}

					if (Directory.Exists(m_tbDestinationPath.Text))
					{ 
					CreateImageHeaderFile(m_tbImgPath.Text, m_tbDestinationPath.Text);
					CreateImageCFile(m_tbImgPath.Text, m_tbDestinationPath.Text);
				}

					m_img.Source = bmp;
                }
            }
        }
    }
}
