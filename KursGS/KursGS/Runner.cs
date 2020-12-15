using System;
using System.Windows;
using System.Windows.Media.Imaging;

namespace KursGS
{
    class Runner
    {
        private BitmapImage MainBitmap;
        private int HeightSprite;
        private int WidthSprite;
        private int SpriteNumber = 0;
        private int SpriteCount;
        public Runner(string uri, int spriteCount)
        {
            MainBitmap = new BitmapImage(new Uri(uri));
            SpriteCount = spriteCount;
            WidthSprite = MainBitmap.PixelWidth / SpriteCount;
            HeightSprite = MainBitmap.PixelHeight;
        }
        public BitmapSource NextSprite()
        {
            if (SpriteNumber == SpriteCount) SpriteNumber = 0;
            BitmapSource bitmapSource = new CroppedBitmap(MainBitmap, new Int32Rect(WidthSprite * SpriteNumber,
                                                               0, WidthSprite, HeightSprite));
            SpriteNumber++;
            return bitmapSource;
        }
    }
}
