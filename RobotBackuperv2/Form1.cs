using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotBackuperv2
{
    public partial class Form1 : Form
    {
        volatile SerialPort serialPort;
        volatile bool isConnected = false;
        volatile bool isBusy = false;
        volatile int mode = 0;
        volatile int portBoxSize;
        volatile String portName;
        volatile String robotName;
        Thread tryConThread;
        Thread checkConThread;
        Thread downloadThread;
        Thread portFinderThread;

        public Form1()
        {
            InitializeComponent();
            findPorts();
            tryConThread = new Thread(tryToConnect);
            checkConThread = new Thread(checkConnection);
            downloadThread = new Thread(downloadBackup);
            //portFinderThread = new Thread(findPorts);
            portName = " ";
            checkConThread.Start();
            consoleWrite("Trying to connect");
            tryConThread.Start();
            downloadThread.Start();
            //portFinderThread.Start();
        }

        private void findPorts()
        {
            string[] Ports;
            //while (true)
            //{
                Ports = SerialPort.GetPortNames();
                portBoxSize = Ports.Length;

                //if (boxPortList.Items.Count != portBoxSize)
                //{
                    boxPortList.Items.Clear();
                    boxPortList.Items.AddRange(Ports);
                    if (portBoxSize != 0)
                    {
                        boxPortList.SelectedIndex = 0;
                    }
                    consoleWrite("Found " + portBoxSize + " ports");
                //}
                
                //Thread.Sleep(5000);
            //}
        }

        private void asyncWrite(String text)
        {

            textConsole.Text += "[" + DateTime.Now.ToString("HH:mm:ss")
                + "]: " + text + Environment.NewLine;
            textConsole.SelectionStart = textConsole.Text.Length;
            textConsole.ScrollToCaret();
        }

        private void consoleWrite(String text)
        {
            if (textConsole.InvokeRequired)
                textConsole.Invoke(new Action(delegate () { asyncWrite(text); }));
            else
                asyncWrite(text);
        }


        void checkConnection()
        {
            while (true)
            {
                if (isConnected && !isBusy)
                {
                    
                    try
                    {
                        serialPort.WriteLine("");
                        string ad = serialPort.ReadTo(">");
                       
                        //break;

                    }
                    catch (Exception e)
                    {
                        isConnected = false;
                        consoleWrite("Disconnected!");
                        consoleWrite("Trying to connect!");
                        serialPort.Close();
                    }
                }
            }
        }

        void tryToConnect()
        {
            while (true)
            {
                if (isConnected == false)
                {

                        serialPort = new SerialPort(portName);
                        serialPort.ReadTimeout = 1000;
                        try
                        {
                            serialPort.Open();
                            serialPort.WriteLine("");
                            string ad = serialPort.ReadTo(">");
                            consoleWrite("Connected to" + portName);
                            isConnected = true;
                        }
                        catch (Exception e)
                        {
                            serialPort.Close();
                        }
                    
                }
            }
        }

        void downloadBackup()
        {
            while(true)
            {
                String dirName = robotName;
                String resp;
                robotName = DateTime.Now.ToString("ddMMyy");
                switch (mode)
                {
                    case 1:
                        serialPort.WriteLine("USB_FDEL " + dirName);
                        while (true)
                        {
                            try
                            {
                                resp = serialPort.ReadTo(">");
                                break;
                            }
                            catch (Exception ex) { };
                        }
                        //USB
                        /*
                         * resp = com.command("USB_FDEL " + dirName);              
                comDelay();

                resp = com.command("USB_MKDIR " + dirName);
                comDelay();

                if (resp[1].ToString().Substring(0, 2) == "(P")
                {
                    consoleWrite("Failed! Please input USB drive");
                    return;
                }
                resp = com.command("USB_SAVE " + dirName + "\\" + RobotName);
                comDelay();
                consoleWrite("Backup saved");

                resp = com.command("USB_SAVE/ELOG " + dirName + "\\" + RobotName);
                comDelay();
                consoleWrite("Error log saved");

                resp = com.command("USB_SAVE/OPLOG " + dirName + "\\" + RobotName);
                comDelay();
                consoleWrite("Operation log saved");
                         */
                        consoleWrite("aaaaaaaa");
                        mode = 0;
                        //isBusy = false;
                        break;
                    case 2:
                        //RS
                        mode = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        private void boxPortList_SelectedIndexChanged(object sender, EventArgs e)
        {
            portName = boxPortList.SelectedItem.ToString();
            try
            {
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }
                
            } catch (Exception ex) { };
            isConnected = false;
        }

        private void textRobotName_TextChanged(object sender, EventArgs e)
        {
            robotName = textRobotName.Text;
        }

        private void trigUSB_Click(object sender, EventArgs e)
        {
            isBusy = true;
            mode = 1;
        }
    }
}
