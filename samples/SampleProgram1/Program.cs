using System;
using System.Linq;
using SCCISharp;

namespace SampleProgram1
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var manager = SoundInterfaceManager.GetInstance())
            {
                manager.Reset();

                if (!CheckConfigFile(manager))
                    manager.ShowConfig();

                DumpInterfaceManager(manager);
            }
        }

        static bool CheckConfigFile(SoundInterfaceManager manager)
        {
            if (manager.InterfaceCount > 0)
                using (var inf = manager.GetInterface(0))
                    for (int i = 0, j = inf.SoundChipCount; i < j; i++)
                        using (var chip = inf.GetSoundChip(i))
                            if (chip.GetInfo().Type != ChipType.None)
                                return true;

            return false;
        }

        static void DumpInterfaceManager(SoundInterfaceManager manager)
        {
            Console.WriteLine("SCCI Version: {0}", manager.Version);
            Console.WriteLine("Interface Count: {0}", manager.InterfaceCount);

            var interfaceCount = manager.InterfaceCount;

            for (int i = 0; i < interfaceCount; i++)
            {
                using (var soundInterface = manager.GetInterface(i))
                    DumpInterface(soundInterface, manager.GetInterfaceInfo(i), i);
            }
        }

        static void DumpInterface(SoundInterface soundInterface, InterfaceInfo info, int number)
        {
            Console.WriteLine("\t#{0} [{1}] ----------", number, info.Name);
            Console.WriteLine("\tDelay: {0} ms", soundInterface.Delay);
            Console.WriteLine("\tLowLevelAPI: {0}support", soundInterface.IsSupportingLowLevelApi ? "" : "not ");
            Console.WriteLine("\tChip Count: {0}", soundInterface.SoundChipCount);

            var chipCount = soundInterface.SoundChipCount;

            for (int i = 0; i < chipCount; i++)
            {
                using (var chip = soundInterface.GetSoundChip(i))
                    DumpChip(chip, i);
            }

            Console.WriteLine();
        }

        static void DumpChip(SoundChip chip, int number)
        {
            var info = chip.GetInfo();

            Console.WriteLine("\t\t#{0} [{1}] ----------", number, info.Name);
            Console.WriteLine("\t\tType: {0} ({1} Hz)", info.Type, info.Clock);
            Console.WriteLine("\t\tSlot: {0}", info.Slot);
            Console.WriteLine("\t\tLocation: {0}", info.SoundLocation);

            var compatible = info.CompatibleChipType.Zip(info.CompatibleChipClock, (t, c) => string.Format("{0} ({1} Hz)", t, c));
            Console.WriteLine("\t\tCompatible: {0}", string.Join(", ", compatible));
            Console.WriteLine("\t\tUsed: {0}", info.IsUsed);

            Console.WriteLine();
        }
    }
}
