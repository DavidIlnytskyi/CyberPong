using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class BLEManager : MonoBehaviour
{
    public Text statusText;
    public List<InputField> inputFields;

    private string deviceId;
    private string serviceId;

    private Dictionary<MotorDirection, string> motorCharIDs = new Dictionary<MotorDirection, string>();
    private bool connecting;


    private void Start()
    {
        SetUpConnection();
    }
    
    public void SetUpConnection()
    {
        StartCoroutine(SetUpConnectionCoroutine());
    }
    IEnumerator SetUpConnectionCoroutine()
    {
        if (connecting) yield break;
        connecting = true;

        statusText.text = "Searching for nearby CyberPong...";
        yield return StartCoroutine(ConnectToDevice());

        statusText.text = "Searching for required service...";
        yield return StartCoroutine(FindRequiredService());

        statusText.text = "Getting characteristics...";
        yield return StartCoroutine(FindRequiredCharacteristics());

        connecting = false;
        statusText.text = "Connected";
    }
    private IEnumerator ConnectToDevice()
    {
        BleApi.Quit();
        BleApi.StartDeviceScan();
        while (true)
        {
            BleApi.ScanStatus status;
            var res = new BleApi.DeviceUpdate();
            do
            {
                status = BleApi.PollDevice(ref res, false);
                if (status == BleApi.ScanStatus.AVAILABLE)
                {
                    if (!IsCyberPongId(res)) continue; // If it's not CyberPong skip

                    deviceId = res.id;
                    BleApi.StopDeviceScan();
                    yield break;
                }
                else if (status == BleApi.ScanStatus.FINISHED)
                {
                    BleApi.StartDeviceScan();
                }

                yield return null;
            } while (status == BleApi.ScanStatus.AVAILABLE);
        }
    }
    private IEnumerator FindRequiredService()
    {
        BleApi.ScanServices(deviceId);

        while (true)
        {
            BleApi.ScanStatus status;
            do
            {
                status = BleApi.PollService(out var res, false);
                if (status == BleApi.ScanStatus.AVAILABLE)
                {
                    if (res.uuid.Substring(5, 4) == "1815")
                        serviceId = res.uuid;
                }
                else if (status == BleApi.ScanStatus.FINISHED)
                {
                    if (serviceId != "")
                        yield break;
                    BleApi.ScanServices(deviceId);
                }

                yield return null;
            } while (status == BleApi.ScanStatus.AVAILABLE);
        }
    }
    private IEnumerator FindRequiredCharacteristics()
    {
        BleApi.ScanCharacteristics(deviceId, serviceId);

        while (true)
        {
            BleApi.ScanStatus status;
            do
            {
                status = BleApi.PollCharacteristic(out var res, false);
                if (status == BleApi.ScanStatus.AVAILABLE)
                {
                    //{00002a58
                    switch (res.uuid.Substring(5, 4))
                    {
                        case "2a58": motorCharIDs[MotorDirection.Left] = res.uuid; break;
                        case "2a59": motorCharIDs[MotorDirection.Right] = res.uuid; break;
                        case "2a5a": motorCharIDs[MotorDirection.Top] = res.uuid; break;
                        case "2a5b": motorCharIDs[MotorDirection.Bottom] = res.uuid; break;
                    }
                }
                else if (status == BleApi.ScanStatus.FINISHED)
                {
                    if (motorCharIDs.ContainsKey(MotorDirection.Left) &&
                        motorCharIDs.ContainsKey(MotorDirection.Right) &&
                        motorCharIDs.ContainsKey(MotorDirection.Top) &&
                        motorCharIDs.ContainsKey(MotorDirection.Bottom))
                        yield break;
                    BleApi.ScanCharacteristics(deviceId, serviceId);
                }

                yield return null;
            } while (status == BleApi.ScanStatus.AVAILABLE);
        }
    }
    private static bool IsCyberPongId(BleApi.DeviceUpdate res)
    {
        return res.id.Substring(res.id.Length - 17, 17) == "00:ab:cd:dc:ba:00";
    }


    public void WriteMotorSpeeds()
    {
        for (var i = 0; i < inputFields.Count; i++)
        {
            var value = int.Parse(inputFields[i].text);
            Write(motorCharIDs[(MotorDirection)i], value);
        }
    }
    public void Write(string charId, int value)
    {
        var payload = BitConverter.GetBytes(value);
        var data = new BleApi.BLEData
        {
            buf = new byte[512],
            size = (short)payload.Length,
            deviceId = deviceId,
            serviceUuid = serviceId,
            characteristicUuid = charId,
        };
        for (var i = 0; i < payload.Length; i++)
            data.buf[i] = payload[i];
        BleApi.SendData(in data, false);
    }


    public static byte[] StringToByteArray(string hex)
    {
        return Enumerable.Range(0, hex.Length)
            .Where(x => x % 2 == 0)
            .Select(x => Convert.ToByte(hex.Substring(x, 2), 16))
            .ToArray();
    }

    private void OnApplicationQuit()
    {
        BleApi.Quit();
    }
}

public enum MotorDirection
{
    Left,
    Right,
    Top,
    Bottom
}