#pragma once

namespace SCCISharp {

	using namespace System;
	using namespace System::Collections::Generic;

	ref class InterfaceInfo;
	ref class SoundChipInfo;
	ref class SoundInterface;
	ref class SoundInterfaceManager;
	ref class SoundChip;

	/// <summary>
	/// �`�b�v�̎�ނ�\���񋓑̂ł��B
	/// </summary>
	public enum class ChipType
	{
		None = 0,
		YM2608,
		YM2151,
		YM2610,
		YM2203,
		YM2612,
		AY8910,
		SN76489,
		YM3812,
		YMF262,
		YM2413,
		YM3526,
		YMF288,
		SCC,
		SCCS,
		Y8950,
		YM2164,
		YM2414,
		AY8930,
		YM2149,
		YMZ294,
		SN76496,
		YM2420,
		YMF281,
		YMF276,
		YM2610B,
		YMF286,
		YM2602,
		UM3567,
		YMF274,
		YM3806,
		YM2163,
		YM7129,
		YMZ280,
		YMZ705,
		YMZ735,
		SPC700,
		MAX
	};

	/// <summary>
	/// �`�b�v�̃��P�[�V��������ʂ��邽�߂̗񋓑̂ł��B
	/// </summary>
	public enum class SoundLocation
	{
		/// <summary>
		/// ���m�����B
		/// </summary>
		Mono = 0,

		/// <summary>
		/// ���`���l���B
		/// </summary>
		Left = 1,

		/// <summary>
		/// �E�`���l���B
		/// </summary>
		Right = 2,

		/// <summary>
		/// �X�e���I�B
		/// </summary>
		Stereo = 3,
	};

	/// <summary>
	/// �C���^�t�F�[�X�Ƃ̒ʐM������\���񋓑̂ł��B
	/// </summary>
	public enum class CommunicationMode
	{
		/// <summary>
		/// �ʐM�͔񓯊��I�ɍs���܂��B
		/// </summary>
		Async = 0x00000000,

		/// <summary>
		/// �ʐM�͓����I�ɍs���܂��B
		/// </summary>
		Sync = 0x00000001,
	};

	/// <summary>
	/// �`�b�v�̎擾���@��\���񋓑̂ł��B
	/// </summary>
	public enum class AcquisitionMode
	{
		/// <summary>
		/// �`�b�v�͎w�肳�ꂽ�^�C�v�ƃN���b�N�ɍł��߂����̂��I������A�擾����܂��B
		/// </summary>
		Near = 0x00000000,

		/// <summary>
		/// �`�b�v�͎w�肳�ꂽ�^�C�v�ƃN���b�N�Ɉ�v������̂��I������A�擾����܂��B
		/// �������A�N���b�N�� SetAcquisitionModeClockRange ���\�b�h�Ŏw�肳�ꂽ�͈͂̒�����I������܂��B
		/// </summary>
		Match = 0x00000001,
	};

	/// <summary>
	/// �C���^�t�F�[�X�̏�Ԃ��i�[�����N���X�ł��B
	/// </summary>
	public ref class InterfaceInfo
	{
	public:
		/// <summary>
		/// �C���^�t�F�[�X�̖��O��\����������擾���܂��B
		/// </summary>
		property String^ Name { String^ get(); }

		/// <summary>
		/// �C���^�t�F�[�X�ɐڑ�����Ă���`�b�v�̑������擾���܂��B
		/// </summary>
		property Int32 SoundChipCount { Int32 get(); }

	internal:
		InterfaceInfo(String^ name, Int32 chipCount);

	private:
		String^ name;
		Int32 chipCount;
	};

	/// <summary>
	/// �`�b�v�̏�Ԃ��i�[�����N���X�ł��B
	/// </summary>
	public ref class SoundChipInfo
	{
	public:
		/// <summary>
		/// �`�b�v�̖��O��\����������擾���܂��B
		/// </summary>
		property String^ Name { String^ get(); }

		/// <summary>
		/// �`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �񋓑̂��擾���܂��B
		/// </summary>
		property ChipType Type { ChipType get(); }

		/// <summary>
		/// ���̃`�b�v�ƌ݊����̂���`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �񋓑̂̃��X�g���擾���܂��B
		/// </summary>
		property IReadOnlyList<ChipType>^ CompatibleChipType { IReadOnlyList<ChipType>^ get(); }

		/// <summary>
		/// �`�b�v�̃N���b�N���g�� (Hz) ���擾���܂��B
		/// </summary>
		property Int32 Clock { Int32 get(); }

		/// <summary>
		/// ���̃`�b�v�ƌ݊����̂���`�b�v�̃N���b�N���g�� (Hz) �̃��X�g���擾���܂��B
		/// </summary>
		property IReadOnlyList<Int32>^ CompatibleChipClock { IReadOnlyList<Int32>^ get(); }

		/// <summary>
		/// �`�b�v���g�p���ł��邩��\���^�U�l���擾���܂��B
		/// </summary>
		property bool IsUsed { bool get(); }

		/// <summary>
		/// �`�b�v���ڑ�����Ă���X���b�g�� ID ���擾���܂��B
		/// </summary>
		property Int32 Slot { Int32 get(); }

		/// <summary>
		/// �`�b�v�̃��P�[�V������\�� <see cref="SCCISharp::SoundLocation"/> �񋓑̂��擾���܂��B
		/// </summary>
		property SCCISharp::SoundLocation SoundLocation { SCCISharp::SoundLocation get(); }

	internal:
		SoundChipInfo(String^ name,
					  ChipType chipType,
					  IReadOnlyList<ChipType>^ compatibleChip,
					  Int32 clock,
					  IReadOnlyList<Int32>^ compatibleChipClock,
					  bool isUsed,
					  Int32 slot,
					  SCCISharp::SoundLocation soundLocation);

	private:
		String^ name;
		ChipType chipType;
		IReadOnlyList<ChipType>^ compatibleChip;
		Int32 clock;
		IReadOnlyList<Int32>^ compatibleChipClock;
		bool isUsed;
		Int32 slot;
		SCCISharp::SoundLocation soundLocation;
	};

	/// <summary>
	/// �C���^�t�F�[�X���Ǘ����邽�߂̃}�l�[�W���N���X�ł��B
	/// </summary>
	public ref class SoundInterfaceManager : IDisposable
	{
	public:
		/// <summary>
		/// �}�l�[�W���̃o�[�W������\�����l���擾���܂��B
		/// </summary>
		/// <value>�o�[�W������\�����l�B</value>
		property Int32 Version { Int32 get(); }

		/// <summary>
		/// �f�B���C���� (ms) ���擾�܂��͐ݒ肵�܂��B
		/// </summary>
		/// <value>�f�B���C���Ԃ�\�� 0 �ȏ�̐��l�B</value>
		property Int32 Delay { Int32 get(); void set(Int32 value); }

		/// <summary>
		/// ���x���f�B�X�v���C���\������Ă��邩��\���^�U�l���擾���܂��B
		/// </summary>
		/// <value>�\������Ă���Ƃ� true�A����ȊO�̂Ƃ� false�B</value>
		property bool ShownLevelDisplay { bool get(); }

		/// <summary>
		/// �ڑ�����Ă���C���^�t�F�[�X�̑������擾���܂��B
		/// </summary>
		/// <value>�C���^�t�F�[�X�̑�����\�� 0 �ȏ�̐��l�B</value>
		property Int32 InterfaceCount { Int32 get(); }

		/// <summary>
		/// �I�u�W�F�N�g��������ꂽ����\���^�U�l���擾���܂��B
		/// </summary>
		/// <value>�������Ă���Ƃ� true�A����ȊO�̂Ƃ� false�B</value>
		property bool IsDisposed { bool get(); }

		/// <summary>
		/// �w�肳�ꂽ�C���^�t�F�[�X�̏�Ԃ��i�[���� <see cref="SCCISharp::InterfaceInfo"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <param name="interfaceNumber">�C���^�t�F�[�X�̔ԍ��B</param>
		/// <returns><see cref="SCCISharp::InterfaceInfo"/> �I�u�W�F�N�g�B</returns>
		InterfaceInfo^ GetInterfaceInfo(Int32 interfaceNumber);

		/// <summary>
		/// �w�肳�ꂽ�C���^�t�F�[�X��\�� <see cref="SCCISharp::SoundInterface"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <param name="interfaceNumber">�C���^�t�F�[�X�̔ԍ��B</param>
		/// <returns><see cref="SCCISharp::SoundInterface"/> �I�u�W�F�N�g�B</returns>
		SoundInterface^ GetInterface(Int32 interfaceNumber);

		/// <summary>
		/// �S�ẴC���^�t�F�[�X�̃��\�[�X��������܂��B
		/// </summary>
		/// <returns>����ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool ReleaseAllInterfaces();

		/// <summary>
		/// �w�肳�ꂽ�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <param name="soundChipType">�`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l�B</param>
		/// <param name="clock">�`�b�v�̃N���b�N���g�� (Hz)�B</param>
		/// <returns><see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g�B</returns>
		SoundChip^ GetSoundChip(ChipType soundChipType, Int32 clock);

		/// <summary>
		/// �w�肳�ꂽ�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <param name="soundChipType">�`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l�B</param>
		/// <param name="clockMhz">�`�b�v�̃N���b�N���g�� (MHz)�B</param>
		/// <returns><see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g�B</returns>
		SoundChip^ GetSoundChip(ChipType soundChipType, double clockMhz);
		
		/// <summary>
		/// �w�肳�ꂽ�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g���擾���A
		/// �擾�ɐ����������̐^�U�l��ԋp���܂��B
		/// </summary>
		/// <param name="soundChip">�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g�B���̃p�����[�^�͎Q�Ɠn������܂��B</param>
		/// <param name="soundChipType">�`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l�B</param>
		/// <param name="clock">�`�b�v�̃N���b�N���g�� (Hz)�B</param>
		/// <returns>�擾�ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool TryGetSoundChip([System::Runtime::InteropServices::Out] SoundChip^% soundChip, ChipType soundChipType, Int32 clock);

		/// <summary>
		/// �w�肳�ꂽ�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g���擾���A
		/// �擾�ɐ����������̐^�U�l��ԋp���܂��B
		/// </summary>
		/// <param name="soundChip">�`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g�B���̃p�����[�^�͎Q�Ɠn������܂��B</param>
		/// <param name="soundChipType">�`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l�B</param>
		/// <param name="clockMhz">�`�b�v�̃N���b�N���g�� (MHz)�B</param>
		/// <returns>�擾�ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool TryGetSoundChip([System::Runtime::InteropServices::Out] SoundChip^% soundChip, ChipType soundChipType, double clockMhz);

		/// <summary>
		/// �S�Ẵ`�b�v�̃��\�[�X��������܂��B
		/// </summary>
		/// <returns>����ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool ReleaseAllSoundChips();

		/// <summary>
		/// ���x���f�B�X�v���C��\�����܂��B
		/// </summary>
		void ShowLevelDisplay();

		/// <summary>
		/// ���x���f�B�X�v���C����܂��B
		/// </summary>
		void CloseLevelDisplay();

		/// <summary>
		/// �C���^�t�F�[�X�}�l�[�W�������Z�b�g���܂��B
		/// </summary>
		/// <returns>���Z�b�g�ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool Reset();

		/// <summary>
		/// �C���^�t�F�[�X�}�l�[�W�������������܂��B
		/// </summary>
		/// <returns>�������ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool Initialize();

		/// <summary>
		/// �C���^�t�F�[�X�Ƃ̒ʐM���[�h��ݒ肵�܂��B
		/// </summary>
		/// <param name="mode">�ʐM���[�h��\�� <see cref="SCCISharp::CommunicationMode"/> �̒l�B</param>
		void SetMode(CommunicationMode mode);

		/// <summary>
		/// �o�b�t�@���̃f�[�^�𑦎��ɑ��M���܂��B
		/// </summary>
		void FlushData();

		/// <summary>
		/// �o�b�t�@���N���A���܂��B
		/// </summary>
		void ClearBuffer();

		/// <summary>
		/// �`�b�v�̎擾���[�h���w�肵�܂��B
		/// </summary>
		/// <param name="mode">�擾���[�h��\�� <see cref="SCCISharp::AcquisitionMode"/> �̒l�B</param>
		void SetAcquisitionMode(AcquisitionMode mode);

		/// <summary>
		/// �`�b�v�̎擾���[�h�� <see cref="SCCISharp::AcquisitionMode::Match"/> �ł������Ƃ���
		/// ���e�����N���b�N���g�� (Hz) �̕����w�肵�܂��B
		/// </summary>
		/// <param name="clock">���e�����N���b�N���g�� (Hz) �̕��B</param>
		void SetAcquisitionModeClockRange(Int32 clock);

		/// <summary>
		/// �P��� <see cref="SCCISharp::SoundInterfaceManager"/> �N���X�̃C���X�^���X���擾���܂��B
		/// </summary>
		/// <returns><see cref="SCCISharp::SoundInterfaceManager"/> �I�u�W�F�N�g�B</returns>
		static SoundInterfaceManager^ GetInstance();

	internal:
		bool ReleaseInterface(IntPtr soundInterface);
		bool ReleaseSoundChip(IntPtr soundChip);

	private:
		bool isDisposed;

		SoundInterfaceManager();
		~SoundInterfaceManager();
		!SoundInterfaceManager();
		void CheckDisposed();

		ref class SoundInterfaceManagerHolder
		{
		public:
			static initonly SoundInterfaceManager^ instance = gcnew SoundInterfaceManager();
		};
	};

	/// <summary>
	/// �C���^�t�F�[�X�̋@�\���J�v�Z���������N���X�ł��B
	/// </summary>
	public ref class SoundInterface : IDisposable
	{
	public:
		~SoundInterface();

		/// <summary>
		/// ���̃C���^�t�F�[�X���჌�x�� API ���T�|�[�g���Ă��邩�̐^�U�l���擾���܂��B
		/// </summary>
		/// <value>��჌�x�� API ���T�|�[�g����Ă���Ƃ� true�A����ȊO�̂Ƃ� false�B</value>
		property bool IsSupportingLowLevelApi { bool get(); }

		/// <summary>
		/// �f�B���C���� (ms) ���擾�܂��͐ݒ肵�܂��B
		/// </summary>
		/// <value>�f�B���C���Ԃ�\�� 0 �ȏ�̐��l�B</value>
		property Int32 Delay { Int32 get(); void set(Int32 value); }

		/// <summary>
		/// �C���^�t�F�[�X�ɐڑ�����Ă���`�b�v�̑������擾���܂��B
		/// </summary>
		/// <value>�`�b�v�̑�����\�� 0 �ȏ�̐��l�B</value>
		property Int32 SoundChipCount { Int32 get(); }

		/// <summary>
		/// �I�u�W�F�N�g��������ꂽ����\���^�U�l���擾���܂��B
		/// </summary>
		/// <value>�������Ă���Ƃ� true�A����ȊO�̂Ƃ� false�B</value>
		property bool IsDisposed { bool get(); }

		/// <summary>
		/// �w�肳�ꂽ�z����C���^�t�F�[�X�ɑ��M���܂��B
		/// </summary>
		/// <param name="data">���M�����o�C�g�񂪊i�[���ꂽ <see cref="System::Byte"/> �̔z��B</param>
		/// <param name="offset">���M���J�n�����z��̃I�t�Z�b�g�l�B</param>
		/// <param name="length">���M�����o�C�g��̒����B</param>
		/// <returns>���M�ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool SendData(array<Byte>^ data, Int32 offset, Int32 length);

		/// <summary>
		/// �C���^�t�F�[�X����f�[�^����M���A�z��Ɋi�[���܂��B
		/// </summary>
		/// <param name="data">��M�����o�C�g����i�[���� <see cref="System::Byte"/> �̔z��B</param>
		/// <param name="offset">�i�[���J�n�����z��̃I�t�Z�b�g�l�B</param>
		/// <param name="length">��M�����o�C�g��̒����B</param>
		/// <returns>��M�ɐ������A�z��Ɋi�[���ꂽ�o�C�g��̒����B</returns>
		Int32 ReceiveData(array<Byte>^ data, Int32 offset, Int32 length);

		/// <summary>
		/// �C���^�t�F�[�X�����Z�b�g���܂��B
		/// </summary>
		/// <returns>���Z�b�g�ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool Reset();

		/// <summary>
		/// �C���^�t�F�[�X�����������܂��B
		/// </summary>
		/// <returns>�������ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool Initialize();

		/// <summary>
		/// �C���^�t�F�[�X�ɐڑ�����Ă���`�b�v��\�� <see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <param name="number">�`�b�v�̔ԍ��B</param>
		/// <returns><see cref="SCCISharp::SoundChip"/> �I�u�W�F�N�g�B</returns>
		SoundChip^ GetSoundChip(Int32 number);

	internal:
		SoundInterface(SoundInterfaceManager^ manager, void* soundInterface);

	private:
		!SoundInterface();

		bool isDisposed;

		SoundInterfaceManager^ manager;
		void* soundInterface;

		void CheckDisposed();
	};

	/// <summary>
	/// �`�b�v�̋@�\���J�v�Z���������N���X�ł��B
	/// </summary>
	public ref class SoundChip : IDisposable
	{
	public:
		~SoundChip();

		/// <summary>
		/// �`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l���擾���܂��B
		/// </summary>
		/// <value>�`�b�v�̎�ނ�\�� <see cref="SCCISharp::ChipType"/> �̒l�B</value>
		property ChipType Type { ChipType get(); }

		/// <summary>
		/// �`�b�v�̃N���b�N���g�� (Hz) ���擾���܂��B
		/// </summary>
		/// <value>�N���b�N���g�� (Hz)�B</value>
		property Int32 Clock { Int32 get(); }

		/// <summary>
		/// �I�u�W�F�N�g��������ꂽ����\���^�U�l���擾���܂��B
		/// </summary>
		/// <value>�������Ă���Ƃ� true�A����ȊO�̂Ƃ� false�B</value>
		property bool IsDisposed { bool get(); }

		/// <summary>
		/// �`�b�v�̌��݂̏�Ԃ��i�[���� <see cref="SCCISharp::SoundChipInfo"/> �I�u�W�F�N�g���擾���܂��B
		/// </summary>
		/// <returns><see cref="SCCISharp::SoundChipInfo"/> �I�u�W�F�N�g�B</returns>
		SoundChipInfo^ GetInfo();

		/// <summary>
		/// �`�b�v�̎w�肵���A�h���X�Ƀf�[�^���������݂܂��B
		/// </summary>
		/// <param name="address">���W�X�^�̃A�h���X��\�� 0 �ȏ�̐��l�B</param>
		/// <param name="data">�������܂��f�[�^�B</param>
		/// <returns>�������݂ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool SetRegister(Int32 address, Int32 data);

		/// <summary>
		/// �`�b�v�̎w�肵���A�h���X�̃f�[�^��ǂݎ��܂��B
		/// </summary>
		/// <param name="address">���W�X�^�̃A�h���X��\�� 0 �ȏ�̐��l�B</param>
		/// <returns>�ǂݎ��ꂽ���W�X�^�̃f�[�^�l�B</returns>
		Int32 GetRegister(Int32 address);

		/// <summary>
		/// �`�b�v�����������܂��B
		/// </summary>
		/// <returns>�������ɐ��������Ƃ� true�A����ȊO�̂Ƃ� false�B</returns>
		bool Initialize();

	internal:
		SoundChip(SoundInterfaceManager^ manager, void* soundChip);

	private:
		!SoundChip();

		bool isDisposed;

		SoundInterfaceManager^ manager;
		void* soundChip;

		void CheckDisposed();
	};
}
