using Controller;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Sprites
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		private readonly MainController mainController;

		public MainWindow()
		{
			InitializeComponent();

			mainController = new MainController(this);
			DataContext = mainController;

			mainController.RunFight();
		}

		private void Window_KeyDown(object sender, KeyEventArgs e)
		{
			/*Task.Run(() => */mainController.KeyPressed(e.Key);//);
		}

		private void PauseButton_Click(object sender, RoutedEventArgs e)
		{

		}

		private void InfoButton_Click(object sender, RoutedEventArgs e)
		{

		}
	}
}
