using System;
using System.Threading;
using System.Threading.Tasks;
using SCCISharp;

namespace SampleProgram3
{
    internal class Program
    {
        private static SoundChip chip;
        private static volatile bool reqEnd = false;

        private static void Main(string[] args)
        {
            using (var manager = SoundInterfaceManager.GetInstance())
            {
                manager.Reset();
                manager.SetAcquisitionMode(AcquisitionMode.Near);

                if (!manager.TryGetSoundChip(out chip, ChipType.YM2608, 8.0))
                {
                    Console.Error.WriteLine("このサンプルでは {0} が必要です。", ChipType.YM2608);
                    return;
                }

                using (chip)
                {
                    manager.ShowLevelDisplay();

                    var task = Task.Run((Action)Play);
                    Console.ReadKey(true);
                    reqEnd = true;
                    task.Wait();

                    manager.CloseLevelDisplay();
                }
            }
        }

        private static void Play()
        {
            chip.SetRegister(0x11, 0x3f);

            chip.SetRegister(0x18, 0xcf);
            chip.SetRegister(0x19, 0xcf);
            chip.SetRegister(0x1a, 0xcf);
            chip.SetRegister(0x1b, 0xcf);
            chip.SetRegister(0x1c, 0xcf);
            chip.SetRegister(0x1d, 0xcf);

            const int BD = 1, SD = 2, TOP = 4, HH = 8, TOM = 16/*, RIM = 32*/;

            var score = new int[] {
                        TOP | BD,   0,
                        HH,         0,
                        HH | SD,    0,
                        HH | BD,    HH,
                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH,         0,

                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH | BD,    0,
                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH,         0,

                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH | BD,    HH,
                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH,         0,

                        HH | BD,    0,
                        HH,         0,
                        HH | SD,    0,
                        HH | BD,    0,
                        HH | BD,    0,
                        HH,         0,
                        HH | TOM,   0,
                        HH | TOM,   TOM,
                    };

            while (true)
            {
                for (int i = 0; i < score.Length; i++)
                {
                    if (reqEnd)
                        return;

                    if (score[i] != 0)
                        chip.SetRegister(0x10, score[i]);

                    Thread.Sleep(125);
                }
            }
        }
    }
}
