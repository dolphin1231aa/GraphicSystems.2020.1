using System;
using System.Drawing;
using System.Threading;
using System.Windows;
using System.Windows.Media.Imaging;

namespace Model
{
	public partial class SpritePlayer : NotifierBase
	{
		private readonly int initialPosition;

		private int x = 0;

		private readonly Action<Action> invoke;

		private Thickness position;
		private BitmapSource image;
		private int hp = MaxHpAmount;

		private readonly Bitmap bitmap;

		private readonly bool flip;
		public SpritePlayer(string name, int initialPosition, Action<Action> invoke, bool flip = false)
		{
			bitmap = new Bitmap(SpritesPath);

			this.flip = flip;
			//SingleWidth = (bitmap.Width - vShift) / vAmount;
			//SingleHeight = (bitmap.Height - hShift) / hAmount;
			SingleHeight = 95;
			SingleWidth = 135;
			//lastX = SingleHeight * (vAmount - 1);
			Name = name;
			this.initialPosition = initialPosition;
			this.invoke = invoke;

			Start();

			//Task.Run(() => DoStuff(bitmap));
		}

	}

	/// <summary>
	/// Interface part
	/// </summary>
	public partial class SpritePlayer
	{
		public bool IsBusy { get; private set; } = false;

		public string Name { get; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="position">Attacker's position</param>
		public delegate void OnAttackHandler(double position);
		public event OnAttackHandler Attacked;

		public event Action Died;
		public int SingleWidth { get; }

		public int SingleHeight { get; }

		public OnAttackHandler GetOnAttackHandler()
		{
			return CheckDamage;
		}

		public BitmapSource Image
		{
			get => image;

			private set
			{
				image = value;
				NotifyPropertyChanged("Image");
			}
		}

		public int Hp
		{
			get => hp;

			private set
			{
				hp = value;
				NotifyPropertyChanged("Hp");
			}
		}

		public Thickness Position
		{
			get => position;
			private set
			{
				position = value;
				NotifyPropertyChanged("Position");
			}
		}

		public void Start()
		{
			IsBusy = false;
			Hp = MaxHpAmount;

			x = initialPosition;

			Move(x);

			var img = CropImage(0, 0);
			Paint(img);
		}

		public void MoveRight()
		{
			Animation(WalkLine, MoveRightAction);
		}

		public void MoveLeft()
		{
			Animation(WalkLine, MoveLeftAction);
		}

		public void Attack()
		{
			Animation(AttackLine);

			Attacked?.Invoke(position.Left);
		}

	}

	/// <summary>
	/// Sprites part
	/// </summary>
	public partial class SpritePlayer
	{
		private const int RefreshTimeout = 50;

		private void Animation(int row, Action action = null)
		{
			IsBusy = true;

			//TODO: переделать под column, line
			for (int i = 0; i < hAmount; i++)
			{
				x = x >= SingleWidth * (hAmount - 1) ? 0 : x += SingleWidth;

				var img = CropImage(x, row);

				action?.Invoke();
				Paint(img);
			}

			IsBusy = false;
		}

		private Bitmap CropImage(int x, int row)
		{
			Rectangle section = new Rectangle(new System.Drawing.Point(x, row * SingleHeight), new System.Drawing.Size(SingleWidth, SingleHeight));

			Bitmap bmp = new Bitmap(section.Width, section.Height);

			Graphics.FromImage(bmp).DrawImage(bitmap, 0, 0, section, GraphicsUnit.Pixel);

			if (flip)
				bmp.RotateFlip(RotateFlipType.RotateNoneFlipX);

			return bmp;
		}

		private void Paint(Bitmap img)
		{
			Thread.Sleep(RefreshTimeout);

			try
			{
				Invoke(() => Image = img.ToBitmapImage());
			}
			catch (Exception)
			{ }

		}

		private void Invoke(Action action)
		{
			invoke?.Invoke(action);
		}
	}

	/// <summary>
	/// Actions part
	/// </summary>
	public partial class SpritePlayer
	{
		/// <summary>
		/// Calls when player is under attack
		/// </summary>
		/// <param name="position">Attacker's position</param>
		private void CheckDamage(double position)
		{
			if (Math.Abs(position - Position.Left) < (SingleWidth - CollisionLength))
			{
				if (position + SingleWidth > Position.Left)      //if it's the right player
					ReduceHp();

				if (position + SingleWidth < Position.Left)     //if it's the left player
					ReduceHp();
			}
		}

		private void ReduceHp()
		{
			Hp = Hp > Damage ? Hp -= Damage : 0;

			if (CheckHP() == false)
				Die();
		}

		private bool CheckHP() => hp > 0;

		private void Die()
		{
			Animation(DieLine);
			IsBusy = true;

			Died?.Invoke();
		}

		private void MoveRightAction()
		{
			var t = position.Left + StepLength / hAmount;
			if (flip)    //right
			{
				position.Left = t > Max ? position.Left : t;
			}
			else        //left
			{
				position.Left = t > Mid ? position.Left : t;
			}

			Move((int)position.Left);
		}

		private void MoveLeftAction()
		{
			var t = position.Left - StepLength / hAmount;
			if (flip)       //right
			{
				
				position.Left = t < Mid ? position.Left : t;
			}
			else            //left
			{
				position.Left = t < 0 ? position.Left : t;
			}

			Move((int)position.Left);
		}

		private void Move(int x)
		{
			Position = new Thickness(x, PlayerGroundPoint, 0, 0);
		}
	}

	/// <summary>
	/// Constants
	/// </summary>
	public partial class SpritePlayer
	{
		private const int Max = 1050;
		private const int Mid = Max / 2;

		private const int Damage = 40;

		private const string SpritesPath = @"D:\repos\Sprites\Sprites\Resources\khight_sprites2.png";

		private const int StepLength = 50;

		private const int CollisionLength = 15;

		protected const int DieLine = 2;
		protected const int AttackLine = 1;
		protected const int WalkLine = 0;

		private const int PlayerGroundPoint = 445;

		private const int MaxHpAmount = 100;

		/// <summary>
		///	Sprites horizontal amount
		/// </summary>
		protected const int hAmount = 7;

		/// <summary>
		/// Sprites vertical amount
		/// </summary>
		protected const int vAmount = 7;
	}
}
