using System;
using System.Drawing;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media.Imaging;

namespace Model
{
	public static class ConverterHelper
	{
		public static BitmapSource ToBitmapImage(this Bitmap bitmap)
		{
			return Imaging.CreateBitmapSourceFromHBitmap(
						 bitmap.GetHbitmap(),
						 IntPtr.Zero,
						 Int32Rect.Empty,
						 BitmapSizeOptions.FromEmptyOptions());
		}
	}
}
