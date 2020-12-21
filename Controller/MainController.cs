using Model;
using System;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace Controller
{
	public partial class MainController : NotifierBase
	{
		/// <summary>
		/// Actual background img
		/// </summary>
		public BitmapSource BackgroundImage
		{
			get => backgroundImage;

			private set
			{
				backgroundImage = value;
				NotifyPropertyChanged("BackgroundImage");
			}
		}

		public SpritePlayer LeftPlayer { get; }

		public SpritePlayer RightPlayer { get; }

		public int LeftPlayerScore
		{
			get => leftPlayerScore;

			private set
			{
				leftPlayerScore = value;
				NotifyPropertyChanged("LeftPlayerScore");
			}
		}

		public int RightPlayerScore
		{
			get => rightPlayerScore;

			private set
			{
				rightPlayerScore = value;
				NotifyPropertyChanged("RightPlayerScore");
			}
		}

		public MainController(Window window)
		{
			this.window = window;

			InitializeBackgound();

			LeftPlayer = new SpritePlayer(LeftPlayerName, leftPlayerInitialPos, Invoke);
			LeftPlayer.Died += LeftPlayer_Died;

			RightPlayer = new SpritePlayer(RightPlayerName, rightPlayerInitialPos, Invoke, true);
			RightPlayer.Died += RightPlayer_Died;

			LeftPlayer.Attacked += RightPlayer.GetOnAttackHandler();
			RightPlayer.Attacked += LeftPlayer.GetOnAttackHandler();

			Task.Run(() => RunBackgound());

			RunFight();
		}

		public void KeyPressed(Key key)
		{
			var c = GetCommand(key, out var player);
			Task.Run(() => GiveCommand(c, player));
		}

		public void RunFight()
		{
			leftPlayerScore = InitialScore;
			rightPlayerScore = InitialScore;

			NewRound();
		}
	}

	public partial class MainController
	{
		private void NewRound()
		{
			LeftPlayer.Start();
			RightPlayer.Start();
		}

		private void Invoke(Action action)
		{
			try
			{
				window?.Dispatcher.Invoke(action);
			}
			catch (Exception)
			{ }
		}

		private Commands GetCommand(Key key, out SpritePlayer playerN)
		{
			playerN = RightPlayer;
			switch (key)
			{
				case Key.D:
					if (LeftPlayer.IsBusy == false)
					{
						playerN = LeftPlayer;
						return Commands.GoRight;
					}
					goto default;


				case Key.Right:
					if (RightPlayer.IsBusy == false)
						return Commands.GoRight;

					goto default;

				case Key.A:
					if (LeftPlayer.IsBusy == false)
					{
						playerN = LeftPlayer;
						return Commands.GoLeft;
					}
					goto default;

				case Key.Left:
					if (RightPlayer.IsBusy == false)
						return Commands.GoLeft;

					goto default;

				case Key.W:
					if (LeftPlayer.IsBusy == false)
					{
						playerN = LeftPlayer;
						return Commands.Attack;
					}
					goto default;

				case Key.Up:
					if (RightPlayer.IsBusy == false)
						return Commands.Attack;
					goto default;

				default:
					playerN = null;
					return Commands.None;
			}
		}

		private void GiveCommand(Commands command, SpritePlayer player)
		{
			switch (command)
			{
				case Commands.None:
					return;

				case Commands.Attack:
					player.Attack();
					return;

				case Commands.GoRight:
					player.MoveRight();
					return;

				case Commands.GoLeft:
					player.MoveLeft();
					return;

				default:
					throw new ArgumentException($"{nameof(command)} was {command}");
			}
		}

		private int MaxX => (int)window.Width;

		private const int rightPlayerInitialPos = 1050;
		private const int leftPlayerInitialPos = 0;
		private const string LeftPlayerName = "Player1";
		private const string RightPlayerName = "Player2";

		private const int InitialScore = 0;
		private int leftPlayerScore = InitialScore;
		private int rightPlayerScore = InitialScore;
		private readonly object locker = new object();
		private readonly Window window;
	}

	/// <summary>
	/// Players part
	/// </summary>
	public partial class MainController
	{
		private void RightPlayer_Died()
		{
			LeftPlayerScore++;
			NewRound();
		}

		private void LeftPlayer_Died()
		{
			RightPlayerScore++;
			NewRound();
		}
	}

	/// <summary>
	/// Background part
	/// </summary>
	public partial class MainController
	{
		private const int BackgoundSpritesAmount = 6;
		private const int RefreshBackgdoundTimeout = 150;

		private const string UriPrefix = "pack://application:,,,";
		private const string ResourcesFolder = @"/Resources/";
		private const string BackgroundName = "background_";
		private const string BackgorundExt = ".gif";

		private readonly BitmapSource[] backgound = new BitmapSource[BackgoundSpritesAmount];

		private BitmapSource backgroundImage;

		private void InitializeBackgound()
		{
			for (int i = 0; i < BackgoundSpritesAmount; i++)
			{
				var s = $"{UriPrefix}{ResourcesFolder}{BackgroundName}{i}{BackgorundExt}";
				backgound[i] = new BitmapImage(new Uri(s));
			}
		}

		private void RunBackgound()
		{
			for (ulong i = 0; i < ulong.MaxValue; i++)
			{
				Thread.Sleep(RefreshBackgdoundTimeout);
				Invoke(() => BackgroundImage = backgound[i % BackgoundSpritesAmount]);
			}

			//TODO: stop game!
		}
	}
}
