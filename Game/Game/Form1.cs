using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game
{
    public partial class Form1 : Form
    {
        Image playerImage;
        Image playerCalmImage;

        Image coinImage;

        Image part = null;
        Image part1 = null;

        private int currFrame = 0;
        private int currAnimation = -1;

        private int currFrameCoin = 0;
        private int currAnimationCoin = 0;

        private bool isPressedAnyKey = false;

        PictureBox[] coin;

        PictureBox currImage;
        int backgroundspeed;
        Random rnd;

        int score = 0; 

        public Form1()
        {
            InitializeComponent();
           
            playerImage = new Bitmap("C:\\Users\\User\\Desktop\\Start\\STUDY\\5 sem\\GS\\attempts_to_create_a_game\\Game\\sprite_02.png");
            playerCalmImage = new Bitmap("C:\\Users\\User\\Desktop\\Start\\STUDY\\5 sem\\GS\\attempts_to_create_a_game\\Game\\sprite_02_calm.png");

            coinImage = new Bitmap("C:\\Users\\User\\Desktop\\Start\\STUDY\\5 sem\\GS\\attempts_to_create_a_game\\Game\\coin.png");

           

            pictureBox1.Image = playerCalmImage;
            
            //pictureBox1.BackColor = Color.Transparent;
           


            timer2.Interval = 40;
            timer2.Tick += new EventHandler(updMovement);
            timer2.Tick += new EventHandler(update);
            //timer1.Interval = 50;
 
            //timer1.Start();
            timer2.Start();

            timer3.Interval = 250;
            timer3.Tick += new EventHandler(updCoin);
            timer3.Start();

            timer4.Start();

            this.KeyDown += new KeyEventHandler(keyboard);
            this.KeyUp += new KeyEventHandler(freeKeyb);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            backgroundspeed = 7;
            coin = new PictureBox[10];
            rnd = new Random();

           
            part1 = new Bitmap(48, 49);
            Graphics g = Graphics.FromImage(part1);
            g.DrawImage(coinImage, 0, 0, new Rectangle(new Point(48 * currFrameCoin, 49 * currAnimationCoin), new Size(48, 49)), GraphicsUnit.Pixel);

            for (int i = 0; i < coin.Length; i++)
            {
                coin[i] = new PictureBox();
                if (currAnimationCoin != -1)
                {
                    coin[i].Size = new Size(48, 49);
                    coin[i].BackColor = Color.Transparent;
                    coin[i].Location = new Point(rnd.Next(0, 1280), rnd.Next(50, 360));
                    coin[i].Image = part1;

                    this.Controls.Add(coin[i]);
                    coin[i].BringToFront();

                    currImage = coin[i];

                }
    
            }

          
            
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            for (int i = 0; i < coin.Length; i++)
            {
               coin[i].Top += backgroundspeed;

                if (coin[i].Top >= 720)
                {
                    coin[i].Top = coin[i].Height;
                }
            }

            for (int i = coin.Length; i < coin.Length; i++)
            {
                coin[i].Top += backgroundspeed - 10;

                if (coin[i].Top >= 720)
                {
                    coin[i].Top = coin[i].Top;
                }
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (part is null || part1 is null)
            {
                return;
                
            }
            e.Graphics.DrawImage(pictureBox1.Image, pictureBox1.Location);

            for (int i=0; i < coin.Length; i++)
            {
                e.Graphics.DrawImage(coin[i].Image, coin[i].Location);
            }

        }

        private void coinAnimation()
        {
            for (int i = 0; i < coin.Length; i++)
            {
                if (currAnimationCoin != -1)
                {
                    part1 = new Bitmap(54, 60);
                    Graphics g = Graphics.FromImage(part1);
                    g.DrawImage(coinImage, 0, 0, new Rectangle(new Point(54 * currFrameCoin, 60 * currAnimationCoin), new Size(54, 60)), GraphicsUnit.Pixel);
                    coin[i].Image = part1;
                }
            }
        }

        private void updCoin(object sender, EventArgs e)
        {
            coinAnimation();
            if (currFrameCoin == 4)
                currFrameCoin = 0;

            currFrameCoin++;

            for (int i = 0; i < coin.Length; i++)
            {
                if (coin[i].Bounds.IntersectsWith(pictureBox1.Bounds))
                {
                    coin[i].Location = new Point(rnd.Next(0, 1280), 720);
                    score++;

                }
            }

            label1.Text = "Score: " + score;
        }

        private void updMovement(object sender, EventArgs e)
        {
            switch (currAnimation)
            {
                case 0:
                    //currAnimation = 0;
                     pictureBox1.Location = new Point(pictureBox1.Location.X + 25, pictureBox1.Location.Y);
                    break;
                case 1:
                    //currAnimation = 1;
                     pictureBox1.Location = new Point(pictureBox1.Location.X - 25, pictureBox1.Location.Y);
                    break;
                
            }
        }

        private void freeKeyb(object sender, KeyEventArgs e)
        {
           
            isPressedAnyKey = false;
            switch (e.KeyCode.ToString())
            {
                case "D":
                    currAnimation = 4;
                    break;
                case "A":
                    currAnimation = 5;
                    break;
            }
            currFrame = 0;

        }

        private void keyboard(object sender, KeyEventArgs e)
        {
            switch(e.KeyCode.ToString())
            {
                case "D":
                    currAnimation = 0;
                    break;
                case "A":
                    currAnimation = 1;
                    break;
                
            }
            isPressedAnyKey = true;

        }

        private void update(object sender, EventArgs e)
        {
            if (isPressedAnyKey)
            {
                playAnimationMovement();
                if (currFrame == 7)
                    currFrame = 0;
            }
            else
            {
                playAnimationIdle();              
            }

            currFrame++;
        }
        private void playAnimationIdle()
        {
            if (currAnimation >= 4)
            { 
                pictureBox1.Size = new Size(108, 140);
                pictureBox1.Image = playerCalmImage;
            }
        }

        private void playAnimationMovement()
        {
            if (currAnimation != -1 && currAnimation <=3)
            {
                part = new Bitmap(108, 140);
                Graphics g = Graphics.FromImage(part);
                g.DrawImage(playerImage, 0, 0, new Rectangle(new Point(108 * currFrame, 140*currAnimation), new Size(108, 140)), GraphicsUnit.Pixel);
                pictureBox1.Size = new Size(108, 140);
                pictureBox1.Image = part;

            }
        }


        private void label1_Click_1(object sender, EventArgs e)
        {

        }
    }
}
