using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TinkerInCSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            //SpeechLib.SpVoice s = new SpeechLib.SpVoice();
            //s.Speak("Version 2 point 4 point 0 point 0 Revision 3", SpeechLib.SpeechVoiceSpeakFlags.SVSFlagsAsync);
            //s.WaitUntilDone(System.Threading.Timeout.Infinite);
            textBox1.Text = "Thank-you for installing the play-out server with username <spell>admin</spell>";


        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SpeechLib.SpeechVoiceSpeakFlags SpFlags = SpeechLib.SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechLib.SpeechVoiceSpeakFlags.SVSFIsXML;
            SpeechLib.SpVoice speech = new SpeechLib.SpVoice();
            SpeechLib.SpeechStreamFileMode SpFileMode = SpeechLib.SpeechStreamFileMode.SSFMCreateForWrite;
            SpeechLib.SpFileStream SpFileStream = new SpeechLib.SpFileStream();
            SpFileStream.Open("C:\\voice.wav", SpFileMode, false);
            //           speech.AudioOutputStream = SpFileStream;
            speech.Speak(textBox1.Text, SpFlags);
            speech.WaitUntilDone(System.Threading.Timeout.Infinite);
            SpFileStream.Close();
        }
    }
}