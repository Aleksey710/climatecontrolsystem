#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
// Register defines

#define	RTC_SECS	 0
#define	RTC_MINS	 1
#define	RTC_HOURS	 2
#define	RTC_DATE	 3
#define	RTC_MONTH	 4
#define	RTC_DAY		 5
#define	RTC_YEAR	 6
#define	RTC_WP		 7
#define	RTC_TC		 8
#define	RTC_BM		31


static unsigned int masks [] = { 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x07, 0xFF } ;

static int ramTestValues [] =
    { 0x00, 0xFF, 0xAA, 0x55, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0xF0, 0x0F, -1 } ;
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent)
{

    //-------------------------------------------------------------------

#ifdef __arm__
    setupRpi()
#endif // __arm__


    //-------------------------------------------------------------------

//    m_dbUnit            = std::make_shared<DbUnit>();
//    m_scriptUnit        = std::make_shared<ScriptUnit>();
//    m_modbusMasterUnit  = std::make_shared<ModbusMasterUnit>();

//    m_dbUnit            = new DbUnit(this);
//    m_scriptUnit        = new ScriptUnit();
//    m_modbusMasterUnit  = new ModbusMasterUnit();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
//    m_modbusMasterUnit->deleteLater();

//    m_scriptUnit->deleteLater();

//    if(m_modbusMasterUnit.get())
//        m_modbusMasterUnit->deleteLater();

//    if(m_scriptUnit.get())
//        m_scriptUnit->deleteLater();

//    if(m_dbUnit.get())
//        m_dbUnit->deleteLater();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - удален") );
}
//------------------------------------------------------------------------------------
//!
void ClimateControlSystem::setupRpi()
{
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG( QString("ClimateControlSystem - setup Raspberry Pi") );

    ds1302setup   (0, 1, 2) ;

    ramTest ();

    setLinuxClock ();

    for (int i = 0 ; i < 5; ++i)
    {
        int clock [8] ;
        ds1302clockRead (clock) ;

        SEND_TO_LOG(QString("ClimateControlSystem - Тестовое чтение [%1] - %2 %3")
                    .arg( i )
                    .arg( QString("%1:%2:%3")
                          .arg( bcdToD (clock [2], masks [2]) )
                          .arg( bcdToD (clock [1], masks [1]) )
                          .arg( bcdToD (clock [0], masks [0]) )
                        )
                    .arg( QString("%1/%2/%3")
                          .arg( bcdToD (clock [3], masks [3]) )
                          .arg( bcdToD (clock [4], masks [4]) )
                          .arg( bcdToD (clock [6], masks [6]) + 2000 )
                        )
                    );
    }

    //setDSclock ();
    SEND_TO_LOG("*****************************************************************************************");
}
//------------------------------------------------------------------------------------
//! bcdToD: dToBCD:
//!	BCD decode/encode
int ClimateControlSystem::bcdToD (unsigned int byte, unsigned int mask)
{
    unsigned int b1, b2 ;
    byte &= mask ;
    b1 = byte & 0x0F ;
    b2 = ((byte >> 4) & 0x0F) * 10 ;
    return b1 + b2 ;
}
//------------------------------------------------------------------------------------
unsigned int ClimateControlSystem::dToBcd (unsigned int byte)
{
    return ((byte / 10) << 4) + (byte % 10) ;
}
//------------------------------------------------------------------------------------
//! ramTest:
//!	Simple test of the 31 bytes of RAM inside the DS1302 chip
int ClimateControlSystem::ramTest (void)
{
    int addr ;
    int got ;
    int i = 0 ;
    int errors = 0 ;
    int testVal ;

    SEND_TO_LOG("DS1302 RAM TEST");

    testVal = ramTestValues [i] ;

    while (testVal != -1)
    {
        for (addr = 0 ; addr < 31 ; ++addr)
        ds1302ramWrite (addr, testVal) ;

        for (addr = 0 ; addr < 31 ; ++addr)
        if ((got = ds1302ramRead (addr)) != testVal)
        {
            SEND_TO_LOG(QString("DS1302 RAM Failure: Address: %1, Expected: 0x%2, Got: 0x%3")
                        .arg(addr).arg(testVal,0,16).arg(got,0,16));
            //printf ("DS1302 RAM Failure: Address: %2d, Expected: 0x%02X, Got: 0x%02X\n",addr, testVal, got) ;
            ++errors ;
        }
        testVal = ramTestValues [++i] ;
    }

    for (addr = 0 ; addr < 31 ; ++addr)
    ds1302ramWrite (addr, addr) ;

    for (addr = 0 ; addr < 31 ; ++addr)
    if ((got = ds1302ramRead (addr)) != addr)
    {
        SEND_TO_LOG(QString("DS1302 RAM Failure: Address: %1, Expected: 0x%2, Got: 0x%3")
                    .arg(addr).arg(addr,0,16).arg(got,0,16));
//        printf ("DS1302 RAM Failure: Address: %2d, Expected: 0x%02X, Got: 0x%02X\n",
//        addr, addr, got) ;
        ++errors ;
    }

    if (errors == 0)
    {
        SEND_TO_LOG("-- DS1302 RAM TEST: OK");
        //printf ("-- DS1302 RAM TEST: OK\n") ;
    } else {
        SEND_TO_LOG("-- DS1302 RAM TEST FAILURE. %d errors.");
        //printf ("-- DS1302 RAM TEST FAILURE. %d errors.\n", errors) ;
    }

    return 0 ;
}
//------------------------------------------------------------------------------------
//! setLinuxClock:
//! Set the Linux clock from the hardware
int ClimateControlSystem::setLinuxClock (void)
{
    char dateTime [20] ;
    char command [64] ;
    int  clock [8] ;

    SEND_TO_LOG("Setting the Linux Clock from the DS1302... ");
    //fflush (stdout) ;

    ds1302clockRead (clock) ;

    // [MMDDhhmm[[CC]YY][.ss]]

    sprintf (dateTime, "%02d%02d%02d%02d%02d%02d.%02d",
    bcdToD (clock [RTC_MONTH], masks [RTC_MONTH]),
    bcdToD (clock [RTC_DATE],  masks [RTC_DATE]),
    bcdToD (clock [RTC_HOURS], masks [RTC_HOURS]),
    bcdToD (clock [RTC_MINS],  masks [RTC_MINS]),
    20,
    bcdToD (clock [RTC_YEAR],  masks [RTC_YEAR]),
    bcdToD (clock [RTC_SECS],  masks [RTC_SECS])) ;

    sprintf (command, "/bin/date %s", dateTime) ;
    system (command) ;

    return 0 ;
}
//------------------------------------------------------------------------------------
//! setDSclock:
//! Set the DS1302 block from Linux time
int ClimateControlSystem::setDSclock (void)
{
    struct tm t ;
    time_t now ;
    int clock [8] ;

    SEND_TO_LOG("Setting the clock in the DS1302 from Linux time... ");

    now = time (NULL) ;
    gmtime_r (&now, &t) ;

    clock [ 0] = dToBcd (t.tm_sec) ;        // seconds
    clock [ 1] = dToBcd (t.tm_min) ;        // mins
    clock [ 2] = dToBcd (t.tm_hour) ;       // hours
    clock [ 3] = dToBcd (t.tm_mday) ;       // date
    clock [ 4] = dToBcd (t.tm_mon + 1) ;	// months 0-11 --> 1-12
    clock [ 5] = dToBcd (t.tm_wday + 1) ;	// weekdays (sun 0)
    clock [ 6] = dToBcd (t.tm_year - 100) ; // years
    clock [ 7] = 0 ;                        // W-Protect off

    ds1302clockWrite (clock) ;

    SEND_TO_LOG("OK");

    return 0 ;
}
