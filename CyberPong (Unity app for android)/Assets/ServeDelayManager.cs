using System;
using UnityEngine;

public class ServeDelayManager : MonoBehaviour
{
    public float delay; private float delay_;


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
}
