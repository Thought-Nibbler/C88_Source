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
using System.Windows.Shapes;

namespace MediaFoundationTest
{
    /// <summary>
    /// VideoPlayWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class VideoPlayWindow : Window
    {
        public VideoPlayWindow()
        {
            InitializeComponent();
        }

        private void MyD3DImage_IsFrontBufferAvailableChanged(object sender, DependencyPropertyChangedEventArgs e)
        {

        }
    }
}
