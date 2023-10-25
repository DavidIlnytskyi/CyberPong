using DG.Tweening;
using UnityEngine;

public class WindowManager : MonoBehaviour
{
    public RectTransform advancedSettingsWindow;
    public RectTransform defaultSettingsWindow;


    public void ShowAdvancedSettings()
    {
        advancedSettingsWindow.gameObject.SetActive(true);
        advancedSettingsWindow.DOLocalMoveX(0, 0.2f).From(-300);

        defaultSettingsWindow.DOLocalMoveX(300, 0.2f).OnComplete(() => advancedSettingsWindow.gameObject.SetActive(false));

        DOVirtual.Float(0, 1, 0.2f, (v) => advancedSettingsWindow.GetComponent<CanvasGroup>().alpha = v);
    }
    public void HideAdvancedSettings()
    {
        advancedSettingsWindow.DOLocalMoveX(300, 0.2f).OnComplete(() => advancedSettingsWindow.gameObject.SetActive(false));

        defaultSettingsWindow.gameObject.SetActive(true);
        defaultSettingsWindow.DOLocalMoveX(0, 0.2f).From(-300);

        DOVirtual.Float(0, 1, 0.2f, (v) => advancedSettingsWindow.GetComponent<CanvasGroup>().alpha = v);
    }
}
