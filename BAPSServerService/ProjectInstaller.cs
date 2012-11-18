using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using System.Runtime.InteropServices;

namespace BAPSServerService
{
    [RunInstaller(true)]
    public partial class ProjectInstaller : Installer
    {
        public ProjectInstaller()
        {
            InitializeComponent();
#if DEBUG
			this.serviceInstaller1.ServiceName = "BAPS (DEBUG) Server Service";
			this.serviceInstaller1.DisplayName = "BAPS (DEBUG) Server Service";
            this.bapsServiceController.ServiceName = "BAPS (DEBUG) Server Service";

#else
            this.serviceInstaller1.ServiceName = "BAPS Server Service";
			this.serviceInstaller1.DisplayName = "BAPS Server Service";
            this.bapsServiceController.ServiceName = "BAPS Server Service";
#endif
            this.BeforeInstall += new InstallEventHandler(ProjectInstaller_BeforeInstall);
            this.AfterInstall += new InstallEventHandler(ProjectInstaller_AfterInstall);    
        }

        void ProjectInstaller_AfterInstall(object sender, InstallEventArgs e)
        {
            //Our code goes in this event because it is the only one that will do
            //a proper job of letting the user know that an error has occurred,
            //if one indeed occurs. Installation will be rolled back 
            //if an error occurs.

            int iSCManagerHandle = 0;
            int iSCManagerLockHandle = 0;
            int iServiceHandle = 0;
            bool bChangeServiceConfig2 = false;
            modAPI.SERVICE_FAILURE_ACTIONS ServiceFailureActions;
            modAPI.SC_ACTION[] ScActions = new modAPI.SC_ACTION[3];
            //There should be one element for each action. 
            //The Services snap-in shows 3 possible actions.

            bool bCloseService = false;
            bool bUnlockSCManager = false;
            bool bCloseSCManager = false;

            IntPtr iScActionsPointer = new IntPtr();

            try
            {
                //Obtain a handle to the Service Control Manager, 
                //with appropriate rights.
                //This handle is used to open the relevant service.
                iSCManagerHandle = modAPI.OpenSCManagerA(null, null, modAPI.ServiceControlManagerType.SC_MANAGER_ALL_ACCESS);

                //Check that it's open. If not throw an exception.
                if (iSCManagerHandle < 1)
                {
                    throw new Exception("Unable to open the Services Manager.");
                }

                //Lock the Service Control Manager database.
                iSCManagerLockHandle = modAPI.LockServiceDatabase(iSCManagerHandle);

                //Check that it's locked. If not throw an exception.
                if (iSCManagerLockHandle < 1)
                {
                    throw new Exception("Unable to lock the Services Manager.");
                }

                //Obtain a handle to the relevant service, with appropriate rights.
                //This handle is sent along to change the settings. The second parameter
                //should contain the name you assign to the service.
                iServiceHandle = modAPI.OpenServiceA(iSCManagerHandle, this.serviceInstaller1.ServiceName, modAPI.ACCESS_TYPE.SERVICE_ALL_ACCESS);

                //Check that it's open. If not throw an exception.
                if (iServiceHandle < 1)
                {
                    throw new Exception("Unable to open the Service for modification.");
                }

                //To change the Service Failure Actions, create an instance of the
                //SERVICE_FAILURE_ACTIONS structure and set the members to your
                //desired values. See MSDN for detailed descriptions.
                ServiceFailureActions.dwResetPeriod = 600;
                ServiceFailureActions.lpRebootMsg = "Service failed to start! Rebooting...";
                ServiceFailureActions.lpCommand = "SomeCommand.exe Param1 Param2";
                ServiceFailureActions.cActions = ScActions.Length;

                //The lpsaActions member of SERVICE_FAILURE_ACTIONS is a pointer to an
                //array of SC_ACTION structures. This complicates matters a little,
                //and although it took me a week to figure it out, the solution
                //is quite simple.

                //First order of business is to populate our array of SC_ACTION structures
                //with appropriate values.
                ScActions[0].Delay = 0;
                ScActions[0].SCActionType = modAPI.SC_ACTION_TYPE.SC_ACTION_RESTART;
                ScActions[1].Delay = 0;
                ScActions[1].SCActionType = modAPI.SC_ACTION_TYPE.SC_ACTION_RESTART;
                ScActions[2].Delay = 0;
                ScActions[2].SCActionType = modAPI.SC_ACTION_TYPE.SC_ACTION_RESTART;

                //Once that's done, we need to obtain a pointer to a memory location
                //that we can assign to lpsaActions in SERVICE_FAILURE_ACTIONS.
                //We use 'Marshal.SizeOf(New modAPI.SC_ACTION) * 3' because we pass 
                //3 actions to our service. If you have less 
                //actions change the * 3 accordingly.
                iScActionsPointer = Marshal.AllocHGlobal(Marshal.SizeOf(new modAPI.SC_ACTION()) * 3);

                //Once we have obtained the pointer for the memory location we need to
                //fill the memory with our structure. We use the CopyMemory API function
                //for this. Please have a look at it's declaration in modAPI.
                modAPI.CopyMemory(iScActionsPointer, ScActions, Marshal.SizeOf(new modAPI.SC_ACTION()) * 3);

                //We set the lpsaActions member 
                //of SERVICE_FAILURE_ACTIONS to the integer
                //value of our pointer.
                ServiceFailureActions.lpsaActions = iScActionsPointer.ToInt32();

                //We call bChangeServiceConfig2 with the relevant parameters.
                bChangeServiceConfig2 = modAPI.ChangeServiceConfig2A(iServiceHandle,
                                                                    modAPI.InfoLevel.SERVICE_CONFIG_FAILURE_ACTIONS, 
                                                                    ref ServiceFailureActions);

                //If the update of the failure actions 
                //are unsuccessful it is up to you to
                //throw an exception or not. The fact that 
                //the failure actions did not update
                //should not impact the functionality of your service.
                if (bChangeServiceConfig2==false)
                {
                    throw new Exception("Unable to set the Service Failure Actions.");
                }
            }
            catch(Exception ex)
            {
                //Throw the exception again so the installer can get to it
                throw new Exception(ex.Message);
            }
            finally
            {
                //Close the handles if they are open.
                Marshal.FreeHGlobal(iScActionsPointer);

                if (iServiceHandle > 0)
                {
                    bCloseService = modAPI.CloseServiceHandle(iServiceHandle);
                }

                if (iSCManagerLockHandle > 0)
                {
                    bUnlockSCManager = modAPI.UnlockServiceDatabase(iSCManagerLockHandle);
                }

                if (iSCManagerHandle != 0)
                {
                    bCloseSCManager = modAPI.CloseServiceHandle(iSCManagerHandle);
                }
            }
            //When installation is done go check out your 
            //handy work using Computer Management!
        }
        public override void Install(System.Collections.IDictionary stateSaver)
        {
            base.Install(stateSaver);
			System.String path = System.IO.Path.GetDirectoryName(Context.Parameters["assemblypath"]);
            
            SpeechLib.SpeechVoiceSpeakFlags SpFlags = SpeechLib.SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechLib.SpeechVoiceSpeakFlags.SVSFIsXML;
            SpeechLib.SpVoice speech = new SpeechLib.SpVoice();
            SpeechLib.SpeechStreamFileMode SpFileMode = SpeechLib.SpeechStreamFileMode.SSFMCreateForWrite;
            SpeechLib.SpFileStream SpFileStream = new SpeechLib.SpFileStream();
            SpFileStream.Open(System.String.Concat(path, "\\Welcome Message.wav"), SpFileMode, false);
            speech.AudioOutputStream = SpFileStream;
            System.String introText = "Thank-you for installing the play-out server from the broadcasting and presenting suite. " +
                                      "By default the server accepts connections on port 1350, the default login is username: admin and password: 1234. " +
                                      "The version of the server service is "+
                                      System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.ToString() +". "+
                                      "The version of the server components is "+
                                      System.Reflection.Assembly.GetAssembly(typeof(BAPSServerAssembly.Utility)).GetName().Version.ToString() + ". " +
                                      "Please refer to the documentation included with this application for further assistance.";
            speech.Speak(introText, SpFlags);
            speech.WaitUntilDone(System.Threading.Timeout.Infinite);
            SpFileStream.Close();

			System.Xml.XmlDocument xd = new System.Xml.XmlDocument();
            xd.Load(System.String.Concat("file://", path, "\\serverstate.xml"));
            System.Xml.XmlNode xn = xd.SelectSingleNode("/bapsserverstate/channel/playlist/entry[2]/filename");
            xn.FirstChild.Value = System.String.Concat(path, "\\Welcome Message.wav");
            xn = xd.SelectSingleNode("/bapsserverstate/channel/playlist/entry[1]/textdata");
            xn.FirstChild.Value = introText;
			xd.Save(System.String.Concat(path,"\\serverstate.xml"));
            try
            {
                this.bapsServiceController.Start();
            }
            catch (System.Exception)
            {
                /** ignore it **/
            }
 
		}

        void ProjectInstaller_BeforeInstall(object sender, InstallEventArgs e)
        {
            if (!Context.Parameters.ContainsKey("CredentialType"))
            {
                this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.User;
                return;
            }
            if (Context.Parameters["CredentialType"].Equals("Predefined"))
            {
                switch (Context.Parameters["PredefinedAccount"])
                {
                    case "Network Service":
                        this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.NetworkService;
                        break;
                    case "Local Service":
                        this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.LocalService;
                        break;
                    case "Local System":
                        this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.LocalSystem;
                        break;
                }
                this.serviceProcessInstaller1.Username = "";
                this.serviceProcessInstaller1.Password = "";
            }
            else
            {
                this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.User;
                if (!Context.Parameters["Passwd"].Equals(Context.Parameters["PasswdConf"]))
                {
                    throw new System.Exception("Passwords do not match");
                }
                if (!Context.Parameters["Uname"].Contains("\\"))
                {
                    Context.Parameters["Uname"] = System.String.Concat(".\\", Context.Parameters["Uname"]);
                }
                this.serviceProcessInstaller1.Username = Context.Parameters["Uname"];
                this.serviceProcessInstaller1.Password = Context.Parameters["Passwd"];
            }
        }
        public override void Commit(System.Collections.IDictionary savedState)
        {
            base.Commit(savedState);
            try
            {
                this.bapsServiceController.Start();
            }
            catch (System.Exception)
            {
                /** ignore it **/
            }
        }
        public override void Rollback(System.Collections.IDictionary savedState)
        {
            base.Rollback(savedState);

        }
        public override void Uninstall(System.Collections.IDictionary savedState)
        {
            base.Uninstall(savedState);
        }
    }
}