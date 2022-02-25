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

using System.Drawing.Text;
using System.IO;
using Microsoft.Win32;

namespace FontTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            //// Load export formats
            m_cbExportFontFormat.Items.Add(PixelFormats.Bgra32);
            m_cbExportFontFormat.Items.Add(PixelFormats.Bgr24);
            m_cbExportFontFormat.Items.Add(PixelFormats.Rgb24);
            m_cbExportFontFormat.Items.Add(PixelFormats.Bgr565);
            m_cbExportFontFormat.SelectedIndex = 0;

            // Load Fonts
            LoadFonts();
 
            // Available font sizes
            for (double i = 8; i <= 200; i += .5)
            {
                m_cbFontSize.Items.Add(i);
            }

            FontWeight[] weights = new FontWeight[] { FontWeights.Thin,
                                                      FontWeights.ExtraLight,
                                                      FontWeights.Light,
                                                      FontWeights.Normal,
                                                      FontWeights.Medium,
                                                      FontWeights.SemiBold,
                                                      FontWeights.Bold,
                                                      FontWeights.ExtraBold,
                                                      FontWeights.Black,
                                                      FontWeights.ExtraBlack, };
            for (int i = 0; i < weights.Length; i++)
            {
                m_cbFontWeight.Items.Add(weights[i]);
            }

            m_cbFont.SelectedValue = m_cbFont.Items[0];
            m_cbFontSize.SelectedValue = 16.0;
            m_cbFontWeight.SelectedValue = FontWeights.Normal;
        }

        private void m_cbFont_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (m_cbFont.SelectedValue != null && m_cbFontSize.SelectedValue != null)
            {
                m_ctrlFontPreview.Family = m_cbFont.SelectedValue.ToString();
                m_ctrlFontPreview.Size = m_cbFontSize.SelectedValue != null ? Convert.ToDouble(m_cbFontSize.SelectedValue) : 16;
                m_ctrlFontPreview.FontWeight = m_cbFontWeight.SelectedValue != null ? (FontWeight)(m_cbFontWeight.SelectedValue) : FontWeights.Normal;
                m_lblFontInfo.Text = m_ctrlFontPreview.FontDescription;
            }
        }

        private void Window_ContentRendered(object sender, EventArgs e)
        {
            m_ctrlFontPreview.Family = m_cbFont.SelectedValue.ToString();
            m_ctrlFontPreview.Size = m_cbFontSize.SelectedValue != null ? Convert.ToDouble(m_cbFontSize.SelectedValue) : 16;
            m_ctrlFontPreview.FontWeight = m_cbFontWeight.SelectedValue != null ? (FontWeight)(m_cbFontWeight.SelectedValue) : FontWeights.Normal;
            m_lblFontInfo.Text = m_ctrlFontPreview.FontDescription;
        }

        private void m_btnExportFont_Click(object sender, RoutedEventArgs e)
        {
            string defaultFilename = m_ctrlFontPreview.Family + "_" + m_ctrlFontPreview.Size + "pt";
            defaultFilename = defaultFilename.Replace(" ", "");

            try
            {
                PixelFormat pxFmt = (PixelFormat)m_cbExportFontFormat.SelectedValue;
                SaveFileDialog fDialog = new SaveFileDialog();
                fDialog.Filter = "C code (*.h,*.c)|*.c|Binary File (*.bin)|*.bin";
                fDialog.FileName = defaultFilename;

                if (fDialog.ShowDialog() == true)
                {
                    string filename = fDialog.FileName;
                    string ext = System.IO.Path.GetExtension(filename);
                    if (ext == ".bin")
                    {
                        Byte[] bytes = m_ctrlFontPreview.GetBinary(pxFmt);
                        SaveToFile(fDialog.FileName, bytes);
                    }
                    else
                    {
                        string hText, cText;
                        m_ctrlFontPreview.GetCCode((PixelFormat)m_cbExportFontFormat.SelectedValue, filename, out hText, out cText);

                        SaveToTextFile(filename, cText);                                            // C File
                        SaveToTextFile(filename.Substring(0, filename.Length-1) + "h", hText);      // Header file

                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Export error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void m_chkNumbersOnly_Checked(object sender, RoutedEventArgs e)
        {
            m_ctrlFontPreview.NumbersOnly = true;
        }

        private void m_chkNumbersOnly_Unchecked(object sender, RoutedEventArgs e)
        {
            m_ctrlFontPreview.NumbersOnly = false;
        }
        private void m_chkMonoOnly_Checked(object sender, RoutedEventArgs e)
        {
            m_ctrlFontPreview.NumbersOnly = true;
        }

        private void m_chkMonoOnly_Unchecked(object sender, RoutedEventArgs e)
        {
            m_ctrlFontPreview.NumbersOnly = false;
        }

        private void LoadFonts()
        {
            // Load all fonts
            InstalledFontCollection installedFontCollection = new InstalledFontCollection();
            foreach (System.Drawing.FontFamily fontFam in installedFontCollection.Families)
            {
                // Mono-spaced fonts only
                if (m_chkMono.IsChecked.Value && fontFam.IsStyleAvailable(System.Drawing.FontStyle.Regular))
                {
                    FormattedText fmtText1 = new FormattedText("WWWWWWWWWW", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, new Typeface(fontFam.Name), 16, Brushes.Black);
                    FormattedText fmtText2 = new FormattedText("iiiiiiiiii", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, new Typeface(fontFam.Name), 16, Brushes.Black);

                    if (fmtText1.Width == fmtText2.Width)
                    {
                        m_cbFont.Items.Add(fontFam.Name);
                    }
                }
                else
                {
                    m_cbFont.Items.Add(fontFam.Name);
                }
            }
        }

        void SaveToFile(string filename, byte[] data)
        {
            FileStream fStream = null;
            try
            {
                    fStream = new FileStream(filename, FileMode.OpenOrCreate);
                    fStream.Write(data, 0, data.Length);
            }
            finally
            {
                if (fStream != null) { fStream.Close(); }
            }
        }

        void SaveToTextFile(string filename, string text)
        {
            System.IO.File.WriteAllText(filename, text);
        }
    }
}
