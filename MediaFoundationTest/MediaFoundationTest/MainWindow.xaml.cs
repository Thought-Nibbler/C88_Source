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
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using PlayMediaFile;
using MFCapture;
using System.ComponentModel;

namespace MediaFoundationTest
{
    /// <summary>
    /// Media Foundation テストプログラムのメインウィンドウ
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        /// <summary>
        /// 動画再生ウィンドウ
        /// </summary>
        private VideoPlayWindow VideoViewer;

        /// <summary>
        /// 動画再生管理
        /// </summary>
        private VideoPlayer MyVideoPlayer;

        /// <summary>
        /// 音声再生管理
        /// </summary>
        private AudioPlayer MyAudioPlayer;

        /// <summary>
        /// カメラキャプチャ管理
        /// </summary>
        private VideoCapture MyVideoCapture;

        #region 動画/音声の再生状態管理
        private enum PlayerState
        {
            Playing = 0,
            Pausing = 1,
            Stopping = 2
        }

        private PlayerState VideoState = PlayerState.Stopping;

        private PlayerState AudioState = PlayerState.Stopping;
        #endregion

        #region バインド用プロパティ
        public bool IsVideoPlayButtonEnable
        {
            get
            {
                return (this.VideoState != PlayerState.Playing);
            }
        }

        public bool IsVideoPauseButtonEnable
        {
            get
            {
                return (this.VideoState == PlayerState.Playing);
            }
        }

        public bool IsVideoStopButtonEnable
        {
            get
            {
                return (this.VideoState != PlayerState.Stopping);
            }
        }

        public bool IsAudioPlayButtonEnable
        {
            get
            {
                return (this.AudioState != PlayerState.Playing);
            }
        }

        public bool IsAudioPauseButtonEnable
        {
            get
            {
                return (this.AudioState == PlayerState.Playing);
            }
        }

        public bool IsAudioStopButtonEnable
        {
            get
            {
                return (this.AudioState != PlayerState.Stopping);
            }
        }

        public bool IsCaptureStartButtonEnabled
        {
            get
            {
                return (this.MyVideoCapture == null);
            }
        }

        public bool IsCaptureEndButtonEnabled
        {
            get
            {
                return (this.MyVideoCapture != null);
            }
        }
        #endregion


        #region 起動時の処理
        public MainWindow()
        {
            InitializeComponent();

            this.DataContext = this;
        }

        private void MainWindow_Load(object sender, RoutedEventArgs e)
        {
        } 
        #endregion

        #region 終了時の処理
        private void MainWindow_Closed(object sender, EventArgs e)
        {
            if (this.VideoViewer != null && this.VideoViewer.IsLoaded)
            {
                this.VideoViewer.Close();
            }

            if (this.MyVideoCapture != null)
            {
                this.MyVideoCapture.Dispose();
                this.MyVideoCapture = null;
            }
        } 
        #endregion

        #region [動画再生]タブ
        private void BtnVideoPlay_Click(object sender, RoutedEventArgs e)
        {
            if (this.VideoViewer == null || !this.VideoViewer.IsLoaded)
            {
                this.VideoViewer = new VideoPlayWindow();
                this.VideoViewer.Show();

                WindowInteropHelper wnd = new WindowInteropHelper(this.VideoViewer);
                this.MyVideoPlayer = new VideoPlayer(wnd.Handle, @"output.mp4");
            }

            bool result = this.MyVideoPlayer.Play();

            if (!result)
            {
                MessageBox.Show("動画の再生に失敗しました。", "Error");
            }

            this.VideoState = PlayerState.Playing;
            this.NotifyPropertyChanged("IsVideoPlayButtonEnable");
            this.NotifyPropertyChanged("IsVideoPauseButtonEnable");
            this.NotifyPropertyChanged("IsVideoStopButtonEnable");
        }

        private void BtnVideoPause_Click(object sender, RoutedEventArgs e)
        {
            bool result = this.MyVideoPlayer.Pause();

            if (!result)
            {
                MessageBox.Show("動画の一時停止に失敗しました。", "Error");
            }

            this.VideoState = PlayerState.Pausing;
            this.NotifyPropertyChanged("IsVideoPlayButtonEnable");
            this.NotifyPropertyChanged("IsVideoPauseButtonEnable");
            this.NotifyPropertyChanged("IsVideoStopButtonEnable");
        }

        private void BtnVideoStop_Click(object sender, RoutedEventArgs e)
        {
            bool result = this.MyVideoPlayer.Stop();

            if (!result)
            {
                MessageBox.Show("動画の停止に失敗しました。", "Error");
            }

            this.VideoViewer.Close();

            this.VideoState = PlayerState.Stopping;
            this.NotifyPropertyChanged("IsVideoPlayButtonEnable");
            this.NotifyPropertyChanged("IsVideoPauseButtonEnable");
            this.NotifyPropertyChanged("IsVideoStopButtonEnable");
        } 
        #endregion

        #region [音声再生]タブ
        private void BtnAudioPlay_Click(object sender, RoutedEventArgs e)
        {
            if (this.AudioState == PlayerState.Stopping)
            {
				this.MyAudioPlayer = new AudioPlayer(@"output.mp3");
            }

            bool result = this.MyAudioPlayer.Play();

            if (!result)
            {
                MessageBox.Show("音声の再生に失敗しました。", "Error");
            }

            this.AudioState = PlayerState.Playing;
            this.NotifyPropertyChanged("IsAudioPlayButtonEnable");
            this.NotifyPropertyChanged("IsAudioPauseButtonEnable");
            this.NotifyPropertyChanged("IsAudioStopButtonEnable");
        }

        private void BtnAudioPause_Click(object sender, RoutedEventArgs e)
        {
            bool result = this.MyAudioPlayer.Pause();

            if (!result)
            {
                MessageBox.Show("音声の一時停止に失敗しました。", "Error");
            }

            this.AudioState = PlayerState.Pausing;
            this.NotifyPropertyChanged("IsAudioPlayButtonEnable");
            this.NotifyPropertyChanged("IsAudioPauseButtonEnable");
            this.NotifyPropertyChanged("IsAudioStopButtonEnable");
        }

        private void BtnAudioStop_Click(object sender, RoutedEventArgs e)
        {
            bool result = this.MyAudioPlayer.Stop();

            if (!result)
            {
                MessageBox.Show("音声の停止に失敗しました。", "Error");
            }

            this.AudioState = PlayerState.Stopping;
            this.NotifyPropertyChanged("IsAudioPlayButtonEnable");
            this.NotifyPropertyChanged("IsAudioPauseButtonEnable");
            this.NotifyPropertyChanged("IsAudioStopButtonEnable");
        } 
        #endregion

        #region [カメラキャプチャ]タブ
        private void BtnCaptureStart_Click(object sender, RoutedEventArgs e)
        {
            this.MyVideoCapture = new VideoCapture();

            bool result = this.MyVideoCapture.CreateCapture();
            if (!result)
            {
                MessageBox.Show("キャプチャの作成に失敗しました。");
            }

            result = this.MyVideoCapture.StartCapture();
            if (!result)
            {
                MessageBox.Show("キャプチャの開始に失敗しました。");
            }

            this.NotifyPropertyChanged("IsCaptureStartButtonEnabled");
            this.NotifyPropertyChanged("IsCaptureEndButtonEnabled");
        }

        private void BtnCaptureEnd_Click(object sender, RoutedEventArgs e)
        {
            bool result = this.MyVideoCapture.StopCapture();
            if (!result)
            {
                MessageBox.Show("キャプチャの終了に失敗しました。");
            }
        }
        #endregion

        #region INotifyPropertyChanged の実装
        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged(String propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        } 
        #endregion
    }
}
