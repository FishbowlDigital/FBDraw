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

namespace FontTool
{
    /// <summary>
    /// Interaction logic for ControlFontPreview.xaml
    /// </summary>
    public partial class ControlFontPreview : UserControl
    {

        bool m_bNumbersOnly = false;
        string m_fontFamily = "Code 128";
        double m_fontSize = 16;
        PixelFormat m_pxFmt = PixelFormats.Bgra32;
        char[] m_asciiTable = new char[95];
        char[] m_numbersOnlyChars = new char[] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ',', '%', 'E', 'e', 'x', 'X', '-', '+', '*', '/', '(', ')', '<', '=', '>' };
        public ControlFontPreview()
        {
            InitializeComponent();
            InitializeFontTable();
        }

        // PROPERTIES
        public string Family
        {
            get { return m_fontFamily; }
            set
            {
                m_fontFamily = value;
                InvalidateVisual();
            }
        }

        public double Size
        {
            get { return m_fontSize; }
            set
            {
                m_fontSize = value;
                InvalidateVisual();
            }
        }

        public PixelFormat PxFormat
        {
            get { return m_pxFmt; }
            set
            {
                m_pxFmt = value;
                InvalidateVisual();
            }
        }

        public string FontDescription
        {
            get
            {
                FormattedText fmtText = new FormattedText("A", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, new Typeface(Family), Size, Brushes.Black);
                int width = (int)fmtText.Width;
                int height = (int)fmtText.Height;
                int bytes = width * height * (PxFormat.BitsPerPixel / 8) * (m_bNumbersOnly ? m_numbersOnlyChars.Length : (26 * 3));    // 3 rows of 26 characters

                string desc = Family + "\r\n";
                desc += "Size:      " + width + "x" + height + "\r\n";
                desc += "Table Size: " + bytes + " bytes\r\n";

                return desc;
            }
        }

        public bool NumbersOnly
        {
            get { return m_bNumbersOnly; }
            set
            {
                m_bNumbersOnly = value;
                InvalidateVisual();         // re-draw
            }
        }

        protected void InitializeFontTable()
        {
            for(int i = 0; i < 95; i++)
            {
                m_asciiTable[i] = (char)(32 + i);
            }
        }

        // Drawing
        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);

            Pen pen = new Pen(Brushes.Black, 1);
            drawingContext.DrawRectangle(Brushes.Black, pen, new Rect(this.RenderSize));

            // Settings
            FontFamily family = new FontFamily(Family);
            Typeface face = new Typeface(family, FontStyle, FontWeight, FontStretches.Normal);

            // Calculate Width - use 'I' so it's obvious if this font isn't monospaced
            FormattedText sample = new FormattedText("I", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
            //int width = (int)sample.Width;
            int height = (int)sample.Height;

            if (m_bNumbersOnly)
            {
                // Numbers Only character set
                int x = 0;
                int y = 0;
                foreach (char c in m_numbersOnlyChars)
                {
                    FormattedText fmtText = new FormattedText(c.ToString(), System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
                    drawingContext.DrawText(fmtText, new Point(x, y));

                    x += (int) (fmtText.Width + 0.5);
                }
            }
            else
            {
                // DRaw the font
                int x = 0;
                int y = 0;
                foreach (char c in m_asciiTable)
                {
                    FormattedText fmtText = new FormattedText(c.ToString(), System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
                    drawingContext.DrawText(fmtText, new Point(x, y));

                    x += (int)(fmtText.Width + 0.5);
                }
            }
        }


        public byte[] GetBinary(PixelFormat pxFmt)
        {
            int iBmp = 0;

            // Settings
            FontFamily family = new FontFamily(Family);
            Typeface face = new Typeface(family, FontStyle, FontWeight, FontStretches.Normal);

            // Calculate Width - use 'i' so it's obvious if this font isn't monospaced
            FormattedText sample = new FormattedText("i", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
            int width = (int)sample.Width;
            int height = (int)sample.Height;

            // 26 character alphabet
            int bytesPerPixel = pxFmt.BitsPerPixel / 8;
            int bytesPerBmp = width * height * bytesPerPixel;
            byte[] charTable = new byte[95 * bytesPerBmp];
            byte[] bmpBytes = new byte[bytesPerBmp];

            // Create transparrent pen
            Pen pen = new Pen(Brushes.Transparent, 1);


            if (m_bNumbersOnly)
            {
                // Numbers
                foreach (char c in m_numbersOnlyChars)
                {
                    DrawingVisual drawingVisual = new DrawingVisual();
                    DrawingContext drawingContext = drawingVisual.RenderOpen();

                    // Draw Transparent background
                    drawingContext.DrawRectangle(Brushes.Transparent, pen, new Rect(0, 0, width, height));

                    // Draw text
                    FormattedText fmtText = new FormattedText(c.ToString(), System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
                    drawingContext.DrawText(fmtText, new Point(0, 0));
                    drawingContext.Close();

                    // Create image to draw to
                    RenderTargetBitmap bmp = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
                    BitmapSource outSrc = new FormatConvertedBitmap(bmp, pxFmt, null, 0);

                    // DRaw to bitmap and copy the pixels
                    bmp.Render(drawingVisual);
                    outSrc.CopyPixels(bmpBytes, bmp.PixelWidth * bytesPerPixel, 0);
                    Buffer.BlockCopy(bmpBytes, 0, charTable, iBmp, bytesPerBmp);

                    // Increment char table byte index
                    iBmp += bytesPerBmp;
                }
            }
            else
            {
                //// DRaw the font
                foreach(char c in m_asciiTable)
                {
                    DrawingVisual drawingVisual = new DrawingVisual();
                    DrawingContext drawingContext = drawingVisual.RenderOpen();

                    // Draw Transparent background
                    drawingContext.DrawRectangle(Brushes.Transparent, pen, new Rect(0, 0, width, height));

                    // Draw text
                    FormattedText fmtText = new FormattedText(c.ToString(), System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
                    drawingContext.DrawText(fmtText, new Point(0, 0));
                    drawingContext.Close();

                    // Create image to draw to
                    RenderTargetBitmap bmp = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
                    BitmapSource outSrc = new FormatConvertedBitmap(bmp, pxFmt, null, 0);

                    // DRaw to bitmap and copy the pixels
                    bmp.Render(drawingVisual);
                    outSrc.CopyPixels(bmpBytes, bmp.PixelWidth * bytesPerPixel, 0);
                    Buffer.BlockCopy(bmpBytes, 0, charTable, iBmp, bytesPerBmp);

                    // Increment char table byte index
                    iBmp += bytesPerBmp;
                }
            }

            return charTable;
        }

        public void GetCCode(PixelFormat pxFmt, string fName, out string headerText, out string srcText)
        {
            // Settings
            FontFamily family = new FontFamily(Family);
            Typeface face = new Typeface(family, FontStyle, FontWeight, FontStretches.Normal);

            string fNoExt = System.IO.Path.GetFileNameWithoutExtension(fName);
            string fNoWhite = fNoExt.Replace(' ', '_');
            string fNoExtCap = fNoWhite.ToUpper();

            // Create header information
            StringBuilder sHBuilder = new StringBuilder();
            sHBuilder.Append("/* " + fNoExt + ".h \n");
            sHBuilder.Append(" * Font generated for FBDraw graphics library\n");
            sHBuilder.Append(" * " + Family + ", " + Size + " pt\n");
            sHBuilder.Append(" */\n\n");
            sHBuilder.Append("#ifndef _" + fNoExtCap + "_H\n");
            sHBuilder.Append("#define  _" + fNoExtCap + "_H\n\n");

            sHBuilder.Append("extern FBDraw::FontDescriptor " + fNoWhite + "_desc;\n\n");

            sHBuilder.Append("\n#endif \t\t\t// #define  _" + fNoExtCap + "_H\n\n");
            headerText = sHBuilder.ToString();

            // Now build the C file
            StringBuilder sWidthTable = new StringBuilder();
            sWidthTable.Append("static int __" + fNoWhite + "_widths[CHARACTER_COUNT] = { ");

            StringBuilder sOffsetTable = new StringBuilder();
            sOffsetTable.Append("static int __" + fNoWhite + "_offsets[CHARACTER_COUNT] = { ");

            StringBuilder sImageBuffer = new StringBuilder();
            sImageBuffer.Append("static unsigned char __" + fNoWhite + "_pxbuffer[] = \n");
            sImageBuffer.Append("{\n");


            // Calculate Height
            FormattedText sample = new FormattedText("i", System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
            int defaultWidth = (int)sample.Width;
            int defaultHeight = (int)sample.Height;

 
            //// DRaw the font
            int numChars = m_asciiTable.Length;
            int iChar = 0;
            int iOffset = 0;
            foreach (char c in m_asciiTable)
            {
                DrawingVisual drawingVisual = new DrawingVisual();
                DrawingContext drawingContext = drawingVisual.RenderOpen();

                // Draw Transparent background
                //drawingContext.DrawRectangle(Brushes.Transparent, pen, new Rect(0, 0, width, height));

                // Draw text
                FormattedText fmtText = new FormattedText(c.ToString(), System.Globalization.CultureInfo.CurrentCulture, System.Windows.FlowDirection.LeftToRight, face, Size, Brushes.White);
                drawingContext.DrawText(fmtText, new Point(0, 0));
                drawingContext.Close();

                // dimensions
                int width = (int)(fmtText.Width + 0.5);
                int height = (int)(fmtText.Height + 0.5);
                if (c == ' ')
                {
                    width = defaultWidth;       // workaround for spaces getting culled
                }
                else if (m_bNumbersOnly && !m_numbersOnlyChars.Contains(c))
                {
                    // No image for this character
                    width = 0;
                    height = 0;
                }

                if (c == ' ')
                {
                    width = defaultWidth;       // workaround for spaces getting culled
                }
                else if (m_bNumbersOnly && !m_numbersOnlyChars.Contains(c))
                {
                    // No image for this character
                    width = 0;
                    height = 0;
                }


                bool hasImage = (width > 0) && (height > 0);

 
                // Create image to draw to
                RenderTargetBitmap bmp = null;
                BitmapSource outSrc = null;
                if (hasImage)
                {
                    bmp = new RenderTargetBitmap(width, height, 96, 96, PixelFormats.Pbgra32);
                    outSrc = new FormatConvertedBitmap(bmp, pxFmt, null, 0);

                    // DRaw to bitmap and copy the pixels
                    bmp.Render(drawingVisual);
                }

 
                // Add to tables
                bool lastChar = ++iChar >= numChars;
                sWidthTable.Append(width.ToString() + (lastChar ? "" : ", "));
                sOffsetTable.Append(iOffset.ToString() + (lastChar ? "" : ", "));

                System.Diagnostics.Debug.WriteLine(c + " = " + width);

                if (hasImage)
                {
                    // Output bytes
                    int bytesPerPx = (pxFmt.BitsPerPixel / 8);
                    byte[] pixels = new byte[width * height * bytesPerPx];
                    outSrc.CopyPixels(pixels, bmp.PixelWidth * bytesPerPx, 0);

                    sImageBuffer.Append("\t/* " + c.ToString() + " */ ");
                    for (int i = 0; i < pixels.Length - 1; i++)
                    {
                        sImageBuffer.Append(String.Format("0x{0:X2}, ", pixels[i]));
                    }
                    sImageBuffer.Append(String.Format("0x{0:X2}" + (lastChar ? "\n" : ",\n"), pixels[pixels.Length - 1]));

                    // Increment offset
                    iOffset += (width * height * bytesPerPx);
                }
            }

            // Finish off tables
            sWidthTable.Append(" };\n\n");
            sOffsetTable.Append(" };\n\n");
            sImageBuffer.Append("\n};\n\n");

            // Create C Src
            StringBuilder sCBuilder = new StringBuilder();
            sCBuilder.Append("/* " + fNoExt + ".c \n");
            sCBuilder.Append(" * Font generated for FBDraw graphics library\n");
            sCBuilder.Append(" * " + Family + ", " + Size + " pt\n");
            sCBuilder.Append(" */\n\n");
            sCBuilder.Append("#include \"Font.h\"\n\n");
            sCBuilder.Append(sWidthTable.ToString());
            sCBuilder.Append(sOffsetTable.ToString());
            sCBuilder.Append(sImageBuffer.ToString());


            sCBuilder.Append("/* The Font Descriptor */\n");
            sCBuilder.Append("FBDraw::FontDescriptor " + fNoWhite + "_desc = \n");
            sCBuilder.Append("{\n");
            sCBuilder.Append("\t" + defaultHeight + ",\t\t\t\t\t/* Height */\n");
            sCBuilder.Append("\t__" + fNoWhite + "_widths,\t/* Character width table */\n");
            sCBuilder.Append("\t__" + fNoWhite + "_offsets,\t/* Character image buffer offset */\n");
            sCBuilder.Append("\t__" + fNoWhite + "_pxbuffer\t/* Alphabet image buffer */\n");
            sCBuilder.Append("};\n\n");

            srcText = sCBuilder.ToString();

            System.Diagnostics.Debug.Write(sHBuilder.ToString());
            System.Diagnostics.Debug.Write(sCBuilder.ToString());

        }

    }
}
