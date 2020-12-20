using System;
using System.Windows;
using System.Timers;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace KursGS
{
    public partial class MainWindow : Window
    {
        private Thickness StartThickness;
        private Thickness DefaultEnemy1;
        private Thickness DefaultEnemy2;        
        private int TrackDPix = 0;
        private int SecBeforeStart = 4;
        private int EnemyDistance = 0;
        private bool GameOver = false;
        private double Progress = 0;
        private BitmapImage StadiumBitmap;
        private Runner MainRunner;
        private Runner EnemyRunner1;
        private Runner EnemyRunner2;
        private Timer MyTimer;
        private Timer MainTimer;
        private Timer StartTimer;
        
        public MainWindow()
        {            
            MyTimer = new Timer(125);
            MainTimer = new Timer(50);
            StartTimer = new Timer(1000);

            MyTimer.Elapsed += MyTimer_Elapsed;
            MainTimer.Elapsed += MainTimer_Elapsed;
            StartTimer.Elapsed += StartTimer_Elapsed;

            MainRunner = new Runner("pack://application:,,,/ImageSource/sonic.png", 8);
            EnemyRunner1 = new Runner("pack://application:,,,/ImageSource/mario.png", 8);
            EnemyRunner2 = new Runner("pack://application:,,,/ImageSource/spyro.png", 2);

            StadiumBitmap = new BitmapImage(new Uri("pack://application:,,,/ImageSource/Stadium.png"));

            InitializeComponent();

            StartThickness = TrackImg.Margin;

            DefaultEnemy1 = EnemyRunner1Img.Margin;
            DefaultEnemy2 = EnemyRunner2Img.Margin;

            EnemyRunner1Img.Source = EnemyRunner1.NextSprite();
            EnemyRunner2Img.Source = EnemyRunner2.NextSprite();
            MainRunnerImg.Source = MainRunner.NextSprite();
        }
        private void StartTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Dispatcher.Invoke(new Action(delegate ()
            {
                SecBeforeStart--;
                if (SecBeforeStart == -1)
                {
                    ResultBlock.Text = "";
                    StartTimer.Stop();
                    return;
                }
                if (SecBeforeStart == 0)
                {
                    ResultBlock.Text = "START";
                    MyTimer.Start();
                    MainTimer.Start();
                }
                else ResultBlock.Text = SecBeforeStart.ToString();
            }));
        }
        private void MainTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Dispatcher.Invoke(new Action(delegate ()
            {
                EnemyRunner1Img.Margin = EnemyMove(EnemyRunner1Img.Margin, 2);
                EnemyRunner2Img.Margin = EnemyMove(EnemyRunner2Img.Margin, 3);
                EnemyDistance++;
                if (EnemyDistance == 530) Lose();
            }));
        }
        private Thickness EnemyMove(Thickness thickness, int dx)
        {
            Thickness newThickness = thickness;
            newThickness.Left += dx;
            newThickness.Right -= dx;
            return newThickness;
        }
        private void MyTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Dispatcher.Invoke(new Action(delegate ()
            {               
                EnemyRunner1Img.Source = EnemyRunner1.NextSprite();
                EnemyRunner2Img.Source = EnemyRunner2.NextSprite();

                TrackDPix++;
                Thickness thickness = TrackImg.Margin;
                thickness.Left -= 4;
                thickness.Right += 4;
                if (TrackDPix == 5)
                {
                    TrackImg.Margin = StartThickness;
                    TrackDPix = 0;
                }
                else
                    TrackImg.Margin = thickness;
            }));
        }
        private void Grid_KeyDown(object sender, KeyEventArgs e)
        {
            if (GameOver)
            {
                SecBeforeStart = 4;
                StartTimer.Start();
                GameOver = false;
                EnemyRunner1Img.Margin = DefaultEnemy1;
                EnemyRunner2Img.Margin = DefaultEnemy2;
                StadiumImg.Source = new CroppedBitmap(StadiumBitmap, new Int32Rect(0,136, 500, 136));
                RestartBlock.Visibility = Visibility.Hidden;
                EnemyDistance = 0;
                return;
            }
            if (SecBeforeStart > 0)
            {
                Lose();
                return;
            }
            if (Progress >= 199)
            { 
                Win();
                return;
            }
            Progress++;           

            BitmapSource bitmapSource = new CroppedBitmap(StadiumBitmap, new Int32Rect((int)(Progress * (StadiumBitmap.PixelWidth / 2) / 200),
                                                                                                   136, 500, 136));
            StadiumImg.Source = bitmapSource;
            MainRunnerImg.Source = MainRunner.NextSprite();
            EnemyRunner1Img.Margin = EnemyMove(EnemyRunner1Img.Margin, -8);
            EnemyRunner2Img.Margin = EnemyMove(EnemyRunner2Img.Margin, -8);
        }
        private void Win()
        {
            StopAllTimer();
            ResultBlock.Text = "WIN";
            GameOver = true;
            Progress = 0;
            RestartBlock.Visibility = Visibility.Visible;
        }
        private void Lose()
        {
            StopAllTimer();
            ResultBlock.Text = "LOSE";
            GameOver = true;
            Progress = 0;
            RestartBlock.Visibility = Visibility.Visible;
        }
        private void StopAllTimer()
        {
            MainTimer.Stop();
            MyTimer.Stop();
            StartTimer.Stop();
        }
        private void Play_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            MenuGrid.Visibility = Visibility.Hidden;
            StartTimer.Start();
        }
    }
}
