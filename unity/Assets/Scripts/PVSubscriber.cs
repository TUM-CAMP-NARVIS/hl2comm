//******************************************************************************
// This class demonstrates how to receive and process messages from a client.
// For a sample client implementation see client_umq.py in the viewer directory.
//******************************************************************************
using AOT;
using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;


namespace tcn
{

    public class PV_Sample
    {

        //[StructLayout(LayoutKind.Explicit)]
        //[FieldOffset(0)]
        [StructLayout(LayoutKind.Sequential)]
        public struct NativeType // z_owned_sample_t
        {
            internal UInt64 timestamp;
            internal UInt32 valid;
        }

        public UInt64 Timestamp { get; } 
        public UInt32 Valid { get; }



        internal PV_Sample(NativeType sample)
        {
            Timestamp = sample.timestamp;
            Valid = sample.valid;
        }

        public string ValueToString()
        {
            string result = Timestamp.ToString(); //System.Text.Encoding.UTF8.GetString(Timestamp, 0, Timestamp.Length);
            return result;
        }
    }

    public class PVSubscriber : MonoBehaviour
    {
        [Tooltip("Enter the Subscriber Name.")]
        public string subscriber_name;

        [Tooltip("Enter the Zenoh Topic to Subscribe to.")]
        public string topic_name;


        private UnityAction<bool> haveSessionEvent;

        void OnEnable()
        {
            if (haveSessionEvent == null)
                haveSessionEvent = new UnityAction<bool>(SessionEventCallback);

            // Register to the event
            //
            tcn.hl2comm.RegisterForSessionEvent(haveSessionEvent);
        }

        void OnDisable()
        {
            // Unregister from the event when this object is disabled or destroyed
            //
            tcn.hl2comm.UnregisterSessionEvent(haveSessionEvent);
            StopPVReceiveOnUI();
        }

        private void SessionEventCallback(bool status)
        {
            Debug.Log("Subscribing to topic: " + this.topic_name);
            StartPVReceiveOnUI(OnInternalMessageCallback, this.topic_name);
        }

        // Start is called before the first frame update
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }


        [DllImport(hl2comm.DllName, CallingConvention = CallingConvention.Cdecl)]
        static extern bool StartPVReceiveOnUI(PVSubscriptionCallback cb, string topic);

        [DllImport(hl2comm.DllName, CallingConvention = CallingConvention.Cdecl)]
        static extern bool StopPVReceiveOnUI();

        //Create string param callback delegate
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]  
        internal delegate bool PVSubscriptionCallback(ref tcn.PV_Sample.NativeType PV_sample);
        [MonoPInvokeCallback(typeof(PVSubscriptionCallback))]
        internal bool OnInternalMessageCallback(ref tcn.PV_Sample.NativeType PV_sample)
        {
            tcn.PV_Sample s = new tcn.PV_Sample(PV_sample);  
            this.HandleMessage(s);
            return true;
        }

        void HandleMessage(tcn.PV_Sample PV_sample)
        {
            UnityEngine.Debug.Log("received video message: " + PV_sample.ValueToString());
        }

    }

}
