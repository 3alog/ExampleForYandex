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
using System.IO;
using System.ComponentModel;

namespace BeliyTimer
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    ///
    public partial class MainWindow : Window
    {
        private System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
        private double seconds = 0;
        private string[] str = new string[1];
        private bool pause = false;
        private TagListFile tagListClass = new TagListFile();
        private List<string> tagStringList;
        public List<BoolStringClass> TheList { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            tagListClass.checkFile("tags.txt");
            tagListClass.checkFile("SavePoint.txt");
            TheList = new List<BoolStringClass>();
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.IsEnabled = true;
            timer.Tick += (o, t) => { timerLoh.Content = TimeSpan.FromSeconds(seconds++); };
            timer.Stop();
            fillListBox();
            this.DataContext = this;
        }

        private void isTimerStarted(bool change)
        {
            if (change)
            {
                timer.Start();
                return;
            }
            timer.Stop();
            seconds = 0;
        }

        private void StartButt_Click(object sender, RoutedEventArgs e)
        {
            pause = false;
            isTimerStarted(true);
            changeVisible();
        }

        private void StopButt_Click(object sender, RoutedEventArgs e)
        {
            pause = false;
            timerLoh.Content = TimeSpan.FromSeconds(0);
            isTimerStarted(false);
            changeVisible();
        }

        private void ResetCheckBox_Click(object sender, RoutedEventArgs e)
        {
            uncheckedBox();
            CheckedListBox.Items.Refresh();
        }

        private void Timer_Loaded(object sender, RoutedEventArgs e)
        {
            var timer = new System.Windows.Threading.DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.IsEnabled = true;
            timer.Tick += (o, t) => { dateTimer.Content = DateTime.Now.ToString(); };
            timer.Start();
        }

        private void PointButt_Click(object sender, RoutedEventArgs e)
        {
            File.AppendAllLines("SavePoint.txt", MakeInfoString());
        }

        private void PauseButt_Click(object sender, RoutedEventArgs e)
        {
            pauseTimer();
        }

        private void DeleteTagsButt_Click(object sender, RoutedEventArgs e)
        {
            if (showMessWindow())
            {
                removeCheckBox();
                CheckedListBox.Items.Refresh();
            }
        }

        private void TagButt_Click(object sender, RoutedEventArgs e)
        {
            addNewTag();
            CheckedListBox.Items.Refresh();
        }

        private void pauseTimer()
        {
            pause = changeBoolValue(pause);
            if (pause)
            {
                timer.Stop();
                return;
            }
            timer.Start();
        }

        private void makeMainString()
        {
            str[0] = string.Format("Game: {0} | Time of Computer: {1} | Time of Point: {2} | Tags: ",
                textBoxer.Text,
                DateTime.Now.ToString(),
                timerLoh.Content
            );
        }

        private void addNewTag()
        {
            TheList.Add(new BoolStringClass { IsSelected = false, TheText = TagTextBoxer.Text });
            tagStringList.Add(TagTextBoxer.Text);
            tagListClass.saveItems("tags.txt", tagStringList);
        }

        private void addTagsToString()
        {
            List<BoolStringClass> theList = TheList.FindAll(x => x.IsSelected.Equals(true));
            for (int i = 0; i < theList.Count; i++)
            {
                if (i == 0)
                {
                    str[0] = str[0] + theList[i].TheText;
                    continue;
                }
                str[0] = str[0] + ", " + theList[i].TheText;
            }
        }

        private bool showMessWindow()
        {
            MessageBoxResult dialogResult = MessageBox.Show("Удалить теги?", "Tag Destroyer", MessageBoxButton.YesNo);
            if (dialogResult == MessageBoxResult.Yes)
            {
                return true;
            }
            return false;

        }

        private string[] MakeInfoString()
        {
            makeMainString();
            addTagsToString();
            return str;
        }

        private bool changeBoolValue(bool value)
        {
            return value = !value;
        }

        private void swapVisible(Button value)
        {
            if (value.Visibility == Visibility.Hidden)
            {
                value.Visibility = Visibility.Visible;
                return;
            }
            value.Visibility = Visibility.Hidden;
        }

        private void сhangeBoolEnable(Button value)
        {
            value.IsEnabled = !value.IsEnabled;
        }

        private void changeVisible()
        {
            swapVisible(StopButt);
            swapVisible(StartButt);
            сhangeBoolEnable(PauseButt);
            сhangeBoolEnable(PointButt);
        }

        private void removeCheckBox()
        {
            TheList.RemoveAll(x => x.IsSelected.Equals(true));
            tagStringList.Clear();
            for (int i = 0; i < TheList.Count; i++)
            {
                tagStringList.Add(TheList[i].TheText);
            }
            tagListClass.saveItems("tags.txt", tagStringList);
        }

        private void uncheckedBox()
        {
            for (int i = 0; i < TheList.FindAll(x => x.IsSelected.Equals(true)).Capacity; i++)
            {
                int j = TheList.FindIndex(x => x.IsSelected.Equals(true));
                TheList[j].IsSelected = false;
            }
        }

        private void fillListBox()
        {
            tagStringList = tagListClass.getItems("tags.txt");
            for (int i = 0; i < tagStringList.Capacity; i++)
            {
                TheList.Add(new BoolStringClass { IsSelected = false, TheText = tagStringList[i] });
            }
        }

        private bool checkMinSec(TextBox txt)
        {
            if (txt.Text.Length != 0)
            {
                if (int.Parse(txt.Text) >= 60)
                {
                    return false;
                }
            }
            return true;
        }

        private bool checkDigit(TextBox txt)
        {
            if (txt.Text.Length > 0)
            {
                for(int i = 0;i < txt.Text.Length; i++)
                {
                    if (char.IsDigit(txt.Text, i))
                    {
                        continue;
                    }
                    return false;
                }
            }
            return true;
        }

        private int translator(TextBox txt)
        {
            if (txt.Text.Length != 0)
            {
                return int.Parse(txt.Text);
            }
            return 0;
        }

        private void PutTimeButt_Click(object sender, RoutedEventArgs e)
        {
            if (checkDigit(HourBoxer) && checkDigit(MinBoxer) && checkDigit(SecBoxer))
            {
                if (checkMinSec(MinBoxer) && checkMinSec(SecBoxer))
                {
                    seconds = translator(SecBoxer) + translator(MinBoxer) * 60 + translator(HourBoxer) * 3600;
                    timerLoh.Content = TimeSpan.FromSeconds(seconds);
                }
            }
        }
    }

    public class BoolStringClass
    {
        public string TheText { get; set; }
        public bool IsSelected { get; set; }
    }
}
