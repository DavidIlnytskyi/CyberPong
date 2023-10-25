namespace Android.BLE.Commands
{
    public abstract class BleCommand
    {
        public float Timeout => _timeout;
        protected float _timeout = 0.5f;

        public readonly bool RunParallel;
        public readonly bool RunContinuously;

        protected BleCommand(bool runParallel = false, bool runContinuously = false)
        {
            RunParallel = runParallel;
            RunContinuously = runContinuously;
        }

        public abstract void Start();

        public virtual void End() { }

        public virtual void EndOnTimeout() => End();

        public virtual bool CommandReceived(BleObject obj)
        {
            return false;
        }
    }
}