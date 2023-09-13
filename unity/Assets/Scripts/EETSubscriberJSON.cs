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

    [System.Serializable]
    public class EETSampleJSON
    {
        public UInt64 Timestamp;
        public Vector3 Position;
        public Quaternion Orientation;
        public Vector3 CenterOrigin;
        public Vector3 CenterDirection;
        public Vector3 LeftOrigin;
        public Vector3 LeftDirection;
        public Vector3 RightOrigin;
        public Vector3 RightDirection;
        public float LeftOpenness;
        public float RightOpenness;
        public float VergenceDist;
        public UInt32 Valid;

        public static EETSampleJSON CreateFromJSON(string jsonString)
        {
            return JsonUtility.FromJson<EETSampleJSON>(jsonString);
        }

        // Given JSON input:
        // {"name":"Dr Charles","lives":3,"health":0.8}
        // this example will return a PlayerInfo object with
        // name == "Dr Charles", lives == 3, and health == 0.8f.
    }

    public class EETSubscriberJSON : MonoBehaviour
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
        }

        private void SessionEventCallback(bool status)
        {
            Debug.Log("Subscribing to topic: " + this.topic_name);
            RegisterRawZSubscriber(this.subscriber_name, this.topic_name, OnInternalMessageCallback);
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
        static extern void RegisterRawZSubscriber(string name, string keyexpr, ZenohSubscriptionCallback cb);

        //Create string param callback delegate
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void ZenohSubscriptionCallback(ref tcn.Sample.NativeType sample);
        [MonoPInvokeCallback(typeof(ZenohSubscriptionCallback))]
        internal void OnInternalMessageCallback(ref tcn.Sample.NativeType samplePtr)
        {
            tcn.Sample s = new tcn.Sample(samplePtr);
            this.HandleMessage(s);

        }

        void HandleMessage(tcn.Sample sample)
        {
            //UnityEngine.Debug.Log("received some message: " + sample.ValueToString());
            EETSampleJSON value = EETSampleJSON.CreateFromJSON(sample.ValueToString());

            // Add logic for json parsing here

        }

    }

}
