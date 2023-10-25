using System;
using System.Collections.Generic;
using System.Linq;
using Android.BLE;
using Android.BLE.Commands;
using UnityEngine;
using UnityEngine.UI;

public class BLEController : MonoBehaviour
{
    public static BLEController instance;

    public Text statusText;
    public List<InputField> inputFields;
    public Button writeBtn;
    public Button serveBtn;
    public Toggle enabledToggle;

    private string deviceId = null;
    private string serviceId = "1815";
    private Dictionary<MotorDirection, string> motorCharIDs = new Dictionary<MotorDirection, string>
    {
        {MotorDirection.Left, "2A58"},
        {MotorDirection.Right, "2A59"},
        {MotorDirection.Top, "2A5A"},
        {MotorDirection.Bottom, "2A5B"},
    };

    private bool isConnecting;

    private List<short> currentSpeeds;



    private void Awake()
    {
        if (instance != null && instance != this)
        {
            Destroy(this);
            return;
        }
        else
            instance = this;
    }



    private void Start()
    {
        SetUpConnection();
    }

    private void SetUpConnection()
    {
        if (deviceId != null || isConnecting) return;
        isConnecting = true;
        statusText.text = "Searching for nearby CyberPong...";
        BleManager.Instance.QueueCommand(new DiscoverDevices(OnDeviceFound, 5 * 1000));

        isConnecting = false;
        Invoke(nameof(SetUpConnection), 5);
    }
    private void OnDeviceFound(string id, string name)
    {
        Debug.Log(id + " " + name);
        if (deviceId != null) return;
        if (name != "CyberPong") return;

        statusText.text = "Connecting to CyberPong...";
        BleManager.Instance.QueueCommand(new ConnectToDevice(id, OnConnected, OnDisconnected));
    }
    private void OnConnected(string deviceId)
    {
        statusText.text = "Connected";
        this.deviceId = deviceId;
        writeBtn.interactable = true;
        serveBtn.interactable = true;
        enabledToggle.interactable = true;
    }
    private void OnDisconnected(string deviceId)
    {
        this.deviceId = null;
        writeBtn.interactable = false;
        serveBtn.interactable = false;
        enabledToggle.interactable = false;

        BleManager._bleLibrary = null;
        BleManager.Instance.Initialize();

        Invoke(nameof(SetUpConnection), 1f);
    }

    public void WriteMotorSpeeds(List<int> newSpeeds)
    {
        this.currentSpeeds = newSpeeds.ConvertAll((speed) => (short)speed);
        WriteData();
    }
    public void DoServe()
    {
        WriteData(1);
    }
    private List<int> GetSpeedsFromInputBoxes()
    {
        var speeds = new List<int>();
        for (int i = 0; i < 4; i++)
            speeds.Add((short.Parse(inputFields[i].text) * 1000));
        return speeds;
    }

    private void WriteData(byte doServe = 0)
    {
        var bytes = new byte[12];
        var pointer = 0;
        for (var i = 0; i < inputFields.Count; i++)
        {
            var bytes_ = BitConverter.GetBytes(currentSpeeds[i]);
            foreach (var b in bytes_)
            {
                bytes[pointer] = b;
                pointer++;
            }
        }

        bytes[8] = doServe;
        bytes[9] = doServe;
        bytes[10] = Convert.ToByte(enabledToggle.isOn);
        bytes[11] = Convert.ToByte(enabledToggle.isOn);
        BleManager.Instance.QueueCommand(new WriteToCharacteristic(deviceId, serviceId, "2A5A", bytes.ToArray()));
    }

    public static byte[] StringToByteArray(string hex)
    {
        return Enumerable.Range(0, hex.Length)
            .Where(x => x % 2 == 0)
            .Select(x => Convert.ToByte(hex.Substring(x, 2), 16))
            .ToArray();
    }



    public enum MotorDirection
    {
        Left,
        Right,
        Top,
        Bottom
    }
}