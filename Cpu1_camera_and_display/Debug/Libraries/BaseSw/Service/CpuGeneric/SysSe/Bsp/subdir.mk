################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.c"
OBJ_FILES += "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.o"
"Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.o" : "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.c" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.opt"

"Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.opt" : .refresh
	@argfile "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.opt" -o "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.o" "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.c" -Ctc26x --lsl-core=vtc -t -I"C:\Users\1004\learngit\Cpu1_camera_and_display" -Wa-H"sfr/regtc26x.def" -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 -I"C:\Users\1004\learngit\Cpu1_camera_and_display\CODE" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Build" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Impl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_PinMap" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Asc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Lin" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Spi" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Icu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Cam" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\CStart" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Irq" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Trap" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Dma" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Dts" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Eray" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Crc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Fft" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Trig" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Hssl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\I2c" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Driver" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Msc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Can" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Io" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Psi5" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Sent" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Src" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Src\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Adc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform\Tricore" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform\Tricore\Compilers" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr\TC26B" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr\TC26B\_Reg" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Service" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Service\CpuGeneric" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_libraries" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_libraries\common" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_peripheral" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\USER" --iso=99 --language=-gcc,-volatile,+strings,-kanji --fp-model=3 --switch=auto --align=0 --default-near-size=0 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=0 -g -Wc-wW557 --error-limit=42 --source -c --dep-file="Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.d" -Wc--make-target="Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.o"
DEPENDENCY_FILES += "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.d"

C_FILES += "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.c"
OBJ_FILES += "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.o"
"Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.o" : "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.c" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.opt"

"Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.opt" : .refresh
	@argfile "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.opt" -o "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.o" "..\Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.c" -Ctc26x --lsl-core=vtc -t -I"C:\Users\1004\learngit\Cpu1_camera_and_display" -Wa-H"sfr/regtc26x.def" -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 -I"C:\Users\1004\learngit\Cpu1_camera_and_display\CODE" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Build" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Impl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\DataHandling" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_Lib\InternalMux" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\_PinMap" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Asc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Lin" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Spi" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Asclin\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Icu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmBc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TimerWithTrigger" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Ccu6\TPwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Cam" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cif\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\CStart" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Irq" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Cpu\Trap" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Dma" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dma\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Dsadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Rdc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dsadc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Dts" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Dts\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Emem\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Eray" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eray\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Phy_Pef7071" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Eth\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Crc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fce\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Fft" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Fft\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Flash\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\IncrEnc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gpt12\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Pwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Atom\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tim\In" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Pwm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\PwmHl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Tom\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Gtm\Trig" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Hssl" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Hssl\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\I2c" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\I2c\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Driver" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Iom\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Msc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Msc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Mtu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Can" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Multican\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Io" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Port\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Psi5" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Psi5s" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Psi5s\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiMaster" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\SpiSlave" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Qspi\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Scu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Sent" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Sent\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Smu\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Src" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Src\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Stm\Timer" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Adc" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\iLLD\TC26B\Tricore\Vadc\Std" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform\Tricore" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Platform\Tricore\Compilers" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr\TC26B" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Infra\Sfr\TC26B\_Reg" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Service" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\BaseSw\Service\CpuGeneric" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_libraries" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_libraries\common" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\Libraries\seekfree_peripheral" -I"C:\Users\1004\learngit\Cpu1_camera_and_display\USER" --iso=99 --language=-gcc,-volatile,+strings,-kanji --fp-model=3 --switch=auto --align=0 --default-near-size=0 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=0 -g -Wc-wW557 --error-limit=42 --source -c --dep-file="Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.d" -Wc--make-target="Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.o"
DEPENDENCY_FILES += "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.d"


GENERATED_FILES += "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.o" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.opt" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Assert.o.d" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.src" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Assert.lst" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.o" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.opt" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\.Bsp.o.d" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.src" "Libraries\BaseSw\Service\CpuGeneric\SysSe\Bsp\Bsp.lst"
