using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class DefaultSettingsManager : MonoBehaviour
{
    public float delay; private float delay_;
    public string spinDir;
    public int speed;


    private void Update()
    {
        if (delay_ <= 0)
        {
            delay_ = delay;
            BLEController.instance.DoServe();
        }
        else
            delay_ -= Time.deltaTime;
    }

    public void SetDelay(float delay)
    {
        this.delay = delay;
    }

    public void SetSpinDirection(string spinDir)
    {
        this.spinDir = spinDir;
        UpdateSpeedsWithRotation();
    }

    public void SetMotorSpeeds(int speed)
    {
        this.speed = speed;
        UpdateSpeedsWithRotation();
    }
    private void UpdateSpeedsWithRotation()
    {
        BLEController.instance.WriteMotorSpeeds(
            new List<int>
            {
                spinDir == "LEFT" ? 0 : speed,
                spinDir == "RIGHT" ? 0 : speed,
                spinDir == "TOP" ? 0 : speed,
                spinDir == "BOTTOM" ? 0 : speed
            });
    }
}
