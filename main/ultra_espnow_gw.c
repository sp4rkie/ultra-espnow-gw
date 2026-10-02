// ---vvv--- standard includes ---vvv--- 
#include "sdkconfig.h"
#include "mnta.h"

/*
 * a gateway is at least an ESPNOW target
 */
#define ESPNOW_TARGET
#define MYSERVICE_PORT 8888         // enable/disable function

/*
 * setting xxx_INITIATOR defines the way the packets are forwarded
 */
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#if ESP32_(37)        // # esp32-37 _192.168.0.24 aa:bb:cc:00:00:01   ultra_espnow_gw/       ESPNOW_USY_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #3 botland (host13 garage)
#   define DEBUG 1
#   define WIFI_INITIATOR

#   define OTA_SSID UFIRE_SSID
#   define STD_TARGET_HOST "host2.example.com"
#   define STD_TARGET_PORT 8888


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(41) || ESP32_(69)  // # esp32-41 192.168.0.25   aa:bb:cc:00:00:02   ultra_espnow_gw/       *** ESPNOW_001_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #2 botland
                                // # esp32-69 192.168.0.26   aa:bb:cc:00:00:04   ultra_espnow_gw/       *** ESPNOW_002_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #4 botland
#   define DEBUG 1
#   define WIFI_INITIATOR


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(44)      // # esp32-44 192.168.0.12   aa:bb:cc:00:00:03   ultra_espnow_gw/       ESPNOW_TOH_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #1 botland (media room)
#   define DEBUG 1
#   define WIFI_INITIATOR


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(55) || ESP32_(57) || ESP32_(61) || ESP32_(65)  // esp32-55 192.168.0.13   aa:bb:cc:00:00:05   ultra_ap/ wifi         wt32-eth01 v1.4 wireless tag (TENSTAR)
                                                            // esp32-57 192.168.0.14   aa:bb:cc:00:00:06   ultra_ap2/ wifi        wt32-eth01 v1.4 wireless tag (TENSTAR)
                                                            // esp32-61 192.168.0.15   aa:bb:cc:00:00:07   ultra_ap3/ wifi        esp32-eth01 v1.4 V1781
                                                            // esp32-65 192.168.0.16   aa:bb:cc:00:00:08   ultra_ap5/ wifi        esp32-eth01 v1.4 V1781 BOOT-PIN
#   define DEBUG 1
// gateway operation modes 
#define ETH_INITIATOR       
//#define WIFI_INITIATOR      // ONLY needed for OTA over WiFi/ normal operation still is superseded by ETH_INITIATOR
//#define NO_INITIATOR      // working as ESPNOW standalone server/  ATTENTION DUE TO WiFi AP setup for ESPNOW ALT_ESPNOW_GATEWAY

#if !defined(WIFI_INITIATOR)
#define FW_UPGRADE_VIA_ETH  // non existant WiFi forces upgrade via ETH
#endif

#if defined(ETH_INITIATOR)
#  define ETH_OPMODE ETH_OPMODE_ETH

//
// 2 methods to include the proper ETH driver code:
// 
//    1. define _INIT_ETH_LAN8720_ONLY_   # and be happy (works for LAN8720 only)
//    2. the IDF_COMPONENT way (using do NOT define _INIT_ETH_LAN8720_ONLY_)
//        base components for the generalized version of example_eth_init() to work:
//        /home/toh/esp-idf.v5.5/components/esp_eth                               [ /src/phy/esp_eth_phy_lan87xx.c ]
//        /home/toh/esp-idf.v5.5/examples/ethernet/basic/components/ethernet_init [ /ethernet_init.c ]
//
//        base sample user of example_eth_init():
//        /home/toh/esp-idf.v5.5/examples/ethernet/basic/main/ethernet_example_main.c
//
// 
// for the generic LAN CFG to work (method 2, i.e. _INIT_ETH_LAN8720_ONLY_ NOT defined) you must provide
// 
// 1. a proper buildit.cfg with sth. like IDF_COMPONENT=$(cat << '!'... ethernet_init: path: ${IDF_PATH}/examples/ethernet/basic/components/ethernet_init
// 2. a proper SDK_VERS like: sdkconfig_idf_WAVESHARE_S3ETH_16MBFLASH_PSRAM defining CONFIG_EXAMPLE_USE_W5500=y et.al.
//      sdkconfig.defaults_idf_esp32_8MBFLASH_wireless_tag:CONFIG_EXAMPLE_ETH_PHY_LAN87XX=y
//      sdkconfig.defaults_idf_esp32_8MBFLASH_wireless_tag:CONFIG_EXAMPLE_ETH_PHY_RST_GPIO=-1
// 
// so to avoid:
//       panics with: expression: example_eth_init(&eth_handles, &eth_port_cnt) / abort() was called
// for the moment define this:
//

// use the simple way ATM (method 1)
#  define _INIT_ETH_LAN8720_ONLY_

// encomment to use ESPNOW_TOH_CHANNEL default
// #define ESPNOW_CHANNEL ESPNOW_ROTA2I_CHANNEL    // ESPNOW_CHANNEL only required for ETH_INITIATOR (since uses ESPNOW_WIFI_SETUP())
#endif


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(75) || ESP32_(77) || ESP32_(79) || ESP32_(81) || ESP32_(87)
                            // esp32-75 192.168.0.17   aa:bb:cc:00:00:0e?  ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
                            // esp32-77 192.168.0.18   aa:bb:cc:00:00:0a   ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
                            // esp32-79 192.168.0.19   -----------------   ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
                            // esp32-81 192.168.0.20   -----------------   ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
#   define DEBUG 1
#   define RGB_GPIO_NUM 21             // must do this here to allow mcom.h to detect this

// gateway operation modes 
#define ETH_INITIATOR       
//#define WIFI_INITIATOR      // ONLY needed for OTA over WiFi/ normal operation still is superseded by ETH_INITIATOR
//#define NO_INITIATOR      // working as ESPNOW standalone server ATTENTION DUE TO WiFi AP setup for ESPNOW ALT_ESPNOW_GATEWAY

#if !defined(WIFI_INITIATOR)
#define FW_UPGRADE_VIA_ETH  // non existant WiFi forces upgrade via ETH
#endif

#if defined(ETH_INITIATOR)
#  define ETH_OPMODE ETH_OPMODE_ETH
// explanation for _INIT_ETH_LAN8720_ONLY_ see above 
//#  define _INIT_ETH_LAN8720_ONLY_     => BECAUSE ENCOMMENTED -> USE PROPER SDK_VERS=WAVESHARE_S3ETH_16MBFLASH_PSRAM... for this
#endif


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#else
#   error this may not happen
#endif

/*
 * GW_TIMING_TRACE - audible-gap bench 2026_09_15. adds an arrival timestamp to espnow_packet_t
 * (mcom.h, guarded) and reports queue wait / forward duration / queue depth in status field 4.
 * costs one _u64 per queue slot and a snprintf per command.
 *
 * STOOD DOWN 2026_09_15. it is not free to leave armed: the trace occupies status field 4, and
 * status[128] then has only 68 chars left for statmsg where the literal "xxx" left 100. statmsg
 * comes from stat_misc_buf[128] and DOES get long on the ordinary path - tcp_server echoes an
 * unknown command back inside "no valid p-cmd ^...^" - so a status that used to fit gets
 * truncated, loses its trailing ']', fails the remote's parse as err#3, and is then DROPPED by
 * the duplicate-status hack below. the remote just times out with nothing logged anywhere.
 *
 * so re-arm it for a campaign, not permanently.
 */
//#define GW_TIMING_TRACE

/*
 * GW_SERIAL_ECHO - the cheap half of the above: echo ONLY which gateway answered and which serial
 * it was serving, as "g<entity>s<serial>" in status field 4.
 *
 * the status carries no serial of its own, and mysend() on the remote clears espnow_sol_pkt then
 * takes the first frame that arrives - so a straggler from one of the two LOSING gateways, sent
 * 10..40ms behind the winner, is accepted as the NEXT command's status. this is the only way to
 * see that happen, because on a pre-acked row every status is a byte-identical "0/0" and on the
 * bell rows every status bell can return is identical too.
 *
 * ~9 chars against the full trace's ~35, so statmsg keeps ~94 of its 100 chars in status[128]
 * instead of dropping to 68 - the truncation hazard that makes GW_TIMING_TRACE unsafe to leave
 * armed does not really apply here. still a campaign tool, not a permanent fixture
 */
//#define GW_SERIAL_ECHO

#include "mlcf.h"
#ifdef MCFG_LOCAL
#include "mcfg_local.h"
#else
#include "mcfg.h"
#endif
#include "mcom.h"
// ---^^^--- standard includes ---^^^--- 


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#if ESP32_(37)        // # esp32-37 192.168.0.11  aa:bb:cc:00:00:01   ultra_espnow_gw/       seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #3 botland (host13 garage)
#define RELAIS      (gpio_num_t)2
#define LED_PIN1    (gpio_num_t)21      // yellow       // active low
#define ledact(on)  ledctl(LED_PIN1, on, ACT_LOW)
#define relact(on)  ledctl(RELAIS, on, ACT_HGH)

/*
 * spurious WiFi AP disconnects/reconnects are not safely detected
 * -> so supervise with watch dog
 */
#define CONNECTIVITY_WATCHOG


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # esp32-41 192.168.0.25   aa:bb:cc:00:00:02   ultra_espnow_gw/       *** ESPNOW_001_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #2 botland
// # esp32-69 192.168.0.26   aa:bb:cc:00:00:04   ultra_espnow_gw/       *** ESPNOW_002_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #4 botland
// # esp32-44 192.168.0.12   aa:bb:cc:00:00:03   ultra_espnow_gw/       ESPNOW_TOH_GW_MAC seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #1 botland (media room)
#elif ESP32_(41) || ESP32_(69) || ESP32_(44)
#define LED_PIN1    (gpio_num_t)21      // yellow       // active low
#define ledact(on) ledctl(LED_PIN1, on, ACT_LOW)

/*
 * spurious WiFi AP disconnects/reconnects are not safely detected
 * -> so supervise with watch dog
 */
#define CONNECTIVITY_WATCHOG


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(55) || ESP32_(57) || ESP32_(61) || ESP32_(65)
#define LED_PIN1    (gpio_num_t)5   // RXD green    // active low (1. LED of wireless-tag)
#define LED_PIN2    (gpio_num_t)17  // TXD green    // active low (2. LED of wireless-tag)
#define ledact(on) ledctl(LED_PIN1, on, ACT_LOW)
#define lederr(on) ledctl(LED_PIN2, on, ACT_LOW)


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif ESP32_(75) || ESP32_(77) || ESP32_(79) || ESP32_(81) || ESP32_(87)
                                // esp32-75 192.168.0.17   aa:bb:cc:00:00:0e?  ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
                                // esp32-77 192.168.0.18   aa:bb:cc:00:00:0a   ultra_espnow_gw/ wifi  esp32-s3-eth wave share R8MTH4 16MB Flash/ 8MB PSRAM
#define ledact(on)  ws2812_set(0, 0, on)

// as of:
//#define rgb_red(on)   ws2812_set(on, 0, 0)
//#define rgb_green(on) ws2812_set(0, on, 0)
//#define rgb_blue(on)  ws2812_set(0, 0, on)
//#define rgb_off()     ws2812_set(0, 0, 0)


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#else
#   error this may not happen
#endif

#if !defined(relact)
#define relact(a)       // make it void
#endif
#if !defined(ledact)
#define ledact(a)       // make it void
#endif
#if !defined(lederr)
#define lederr(a)       // make it void
#endif

// pre-ack default status
#define STAT_OK     ("#[XX]#[0]#[0]#[xxx]#[0]#[0]\n")

/* ---vvv--- crash forensics ---vvv---------------------------------------------------------------- */
/*
 * a panic on a gateway currently leaves NOTHING behind. the sdkconfig has COREDUMP_ENABLE_TO_NONE,
 * LOG_DEFAULT_LEVEL_NONE, and PANIC_PRINT_REBOOT with PANIC_REBOOT_DELAY_SECONDS 0 - so the
 * backtrace goes to UART0 and the chip reboots at once. esp32-44/75/79 have no serial line to catch
 * it, which leaves the unattended firmware re-check against the OTA server on the next boot as the
 * ONLY externally visible trace that anything happened at all.
 *
 * so keep a breadcrumb across the reset instead. RTC_NOINIT_ATTR (.rtc_noinit, NOLOAD in
 * sections.ld) is the only storage that qualifies: unlike RTC_DATA_ATTR it is never re-initialized
 * from the image, so it survives panic/int-wdt/task-wdt/brownout/esp_restart alike and is garbage
 * ONLY after a true power-on - which cr_magic detects, and which is itself the answer we want
 * ('somebody pulled the plug', not 'it crashed').
 *
 * ESP_ERROR_CHECK is deliberately LEFT IN PLACE at the sites below. the abort should keep happening;
 * we only want to know afterwards which one it was, because every one of them lands on
 * ESP_RST_PANIC and is otherwise indistinguishable. fixing them before we know which one fires
 * would make the crashes go away without ever telling us what they were.
 */
#include "esp_system.h"

#define CRASH_MAGIC 0x9e3779b9u

/*
 * ids are stable - do NOT renumber, they show up in @state output kept in the bench log
 */
#define CR_SITE_NONE        0   // panicked, but not at an instrumented site (stack overflow, wild
                                // pointer, assert elsewhere...) - a MEANINGFUL result, not a gap
#define CR_SITE_ACK_NOINI   1   // esp_now_send(), NO_INITIATOR pre-ack
#define CR_SITE_ACK         2   // esp_now_send(), pre-ack
#define CR_SITE_STATUS      3   // esp_now_send(), status reply after forward_cmd() returned
#define CR_SITE_ADD_PEER    4   // esp_now_add_peer(), peer table full - see the override below

/*
 * esp_err_t values worth recognising in the s<site>:0x<err> field:
 *   0x3067 ESPNOW_NO_MEM     send queue full
 *   0x3068 ESPNOW_FULL       peer list full (20)
 *   0x3069 ESPNOW_NOT_FOUND  peer gone
 *   0x306c ESPNOW_IF         peer ifidx does not match the current interface state
 */

RTC_NOINIT_ATTR _u32 cr_magic;
RTC_NOINIT_ATTR _u32 cr_boots;      // boots since the last power-on
RTC_NOINIT_ATTR _u32 cr_panics;     // of those, how many came up on ESP_RST_PANIC
RTC_NOINIT_ATTR _u32 cr_site;       // breadcrumb of the run that is dying RIGHT NOW
RTC_NOINIT_ATTR _i32 cr_err;
RTC_NOINIT_ATTR _u32 cr_last_site;  // ... carried one boot further, so @state can still report it
RTC_NOINIT_ATTR _i32 cr_last_err;
RTC_NOINIT_ATTR _u32 cr_last_reset;

/*
 * ESP_ERROR_CHECK() that drops a site id in RTC memory before it aborts. expr is evaluated exactly
 * once - the plain ESP_ERROR_CHECK re-evaluates its argument in the failure branch, which would
 * send a second ESPNOW frame on the way down
 */
#define CK_SITE(site, expr) \
do { \
    esp_err_t _rc = (expr); \
    if (_rc != ESP_OK) { \
        cr_site = (site); \
        cr_err = _rc; \
    } \
    ESP_ERROR_CHECK(_rc); \
} while (0)

/*
 * must run before anything else in app_main() can crash
 */
void
crash_log_boot(void)
{
    if (cr_magic != CRASH_MAGIC) {  // power-on: .rtc_noinit holds whatever the RAM came up with
        cr_magic = CRASH_MAGIC;
        cr_boots = 0;
        cr_panics = 0;
        cr_site = CR_SITE_NONE;
        cr_err = 0;
    }
    ++cr_boots;
    cr_last_reset = esp_reset_reason();
    if (cr_last_reset == ESP_RST_PANIC) {
        ++cr_panics;
    }
    /*
     * hand the dying run's breadcrumb over and clear the live one, so a site recorded now can
     * never be mistaken for one recorded three boots ago
     */
    cr_last_site = cr_site;
    cr_last_err = cr_err;
    cr_site = CR_SITE_NONE;
    cr_err = 0;
}

/*
 * the misc field of the @state reply. keep it dense and greppable, it has to fit misc[] below:
 *
 *   r4/b12/p7/s3:0x3067/u3601/h198/m141/n2/d0
 *   |   |   |  |        |     |    |    |  +- commands dropped: espnow_unsol_que was full.
 *   |   |   |  |        |     |    |    |     since boot, pairs with u. NOT lost over the air -
 *   |   |   |  |        |     |    |    |     lost here, after arriving. see mcom.h
 *   |   |   |  |        |     |    |    +----- espnow peers held (aborts at 20, see ESPNOW_ADD_PEER)
 *   |   |   |  |        |     |    +------ min free heap ever, KiB
 *   |   |   |  |        |     +----------- free heap now, KiB
 *   |   |   |  |        +----------------- uptime, seconds
 *   |   |   |  +-------------------------- last crash site : esp_err_t   (s0 == not at a site)
 *   |   |   +----------------------------- panic boots since power-on
 *   |   +--------------------------------- boots since power-on
 *   +------------------------------------- esp_reset_reason() of THIS boot
 */
void
crash_misc_str(_i8p misc, _u32 siz)
{
    esp_now_peer_num_t pn = { 0 };  // stays 0 if a @state arrives before ESPNOW_INIT()

    esp_now_get_peer_num(&pn);
    snprintf(misc, siz, "r%u/b%u/p%u/s%u:0x%x/u%u/h%u/m%u/n%d/d%u",
                (unsigned)cr_last_reset,
                (unsigned)cr_boots,
                (unsigned)cr_panics,
                (unsigned)cr_last_site,
                (unsigned)cr_last_err,
                (unsigned)(esp_timer_get_time() / 1000000),
                (unsigned)(esp_get_free_heap_size() / 1024),
                (unsigned)(esp_get_minimum_free_heap_size() / 1024),
                pn.total_num,
                (unsigned)espnow_unsol_dropped
    );
}
/*
 * ESPNOW_ADD_PEER as mcom.h defines it wraps esp_now_add_peer() in ESP_ERROR_CHECK, and a gateway
 * calls it for EVERY unicast packet it receives - while esp_now_del_peer() is called nowhere in
 * the tree. so the peer table only ever grows, ESP_NOW_MAX_TOTAL_PEER_NUM is 20, and peer 21
 * aborts the device. measured on this bench 2026_08_29 with only two remotes present: entity 77
 * went 2 -> 5 peers inside 16 minutes, i.e. the rest of the house fills it up as well.
 *
 * overridden HERE and not in mcom.h on purpose - that header is shared by all twenty projects and
 * a change there would have to be justified for every one of them. identical body, except the
 * abort now leaves a site id behind so @state can name it afterwards
 */
#undef ESPNOW_ADD_PEER
#define ESPNOW_ADD_PEER(mac) \
do { \
    /* If MAC address does not exist in peer list, add it */ \
    if (!esp_now_is_peer_exist(mac)) { \
        esp_now_peer_info_t peer = { 0 }; \
        /* peer.channel = 0; */   /* keep channel as is / already setup in ESPNOW_WIFI_SETUP() */ \
        peer.ifidx = WIFI_IF_STA; \
        /* peer.encrypt = false; */ \
        memcpy(peer.peer_addr, (mac), ESP_NOW_ETH_ALEN); \
        CK_SITE(CR_SITE_ADD_PEER, esp_now_add_peer(&peer)); \
    } \
} while (0)

/*
 * ...and the counterpart that keeps the table from ever getting there.
 *
 * WHY A FLUSH AND NOT add/use/delete PER COMMAND.
 *
 * a peer entry is needed ONLY to send the reply: the packet that triggers this has already been
 * received, queued and dequeued without one. so the entry could in principle be deleted again
 * after every command. it is not, because that would put a real esp_now_add_peer() on the wake ->
 * status path for EVERY command, where today a repeat sender costs one esp_now_is_peer_exist()
 * lookup and nothing more. that path is 62ms and was tuned in single-digit milliseconds; the cost
 * of an insert inside libespnow.a is not known and is not worth finding out to fix a leak.
 *
 * so: leave the common case exactly as it was, and empty the table wholesale when it approaches
 * the limit. a gateway holds NO permanent peers - ESPNOW_ADD_PEERS() is empty for ESPNOW_TARGET -
 * so a flush loses nothing that is not re-added on demand, and the first command from a sender
 * after a flush pays exactly what the first command after a reboot already pays today.
 *
 * called at the TOP of the loop, before ADD_PEER. that matters: the previous command's status has
 * long since gone out (the task blocked on xQueueReceive in between), so a flush can never delete
 * a peer with a send still in flight. espnow_unsol_task is the only task that adds peers here and
 * it adds at most one per iteration, so the count cannot exceed HIGH_WATER + 1 between checks.
 *
 * the CK_SITE abort in ESPNOW_ADD_PEER above is deliberately LEFT IN. with this guard in place a
 * full table is no longer something the house can cause - it would mean the guard itself failed,
 * which is exactly when a breadcrumb is worth more than a survived command.
 */
#define PEER_HIGH_WATER 16      // of ESP_NOW_MAX_TOTAL_PEER_NUM 20, leaving room to spare

void
peer_flush_if_full(void)
{
    esp_now_peer_num_t pn = { 0 };
    esp_now_peer_info_t peer;
    _u32 n = 0;

    if (esp_now_get_peer_num(&pn) != ESP_OK || pn.total_num < PEER_HIGH_WATER) {
        return;
    }
    /*
     * always fetch from the head and delete that one, rather than walking with from_head=false:
     * deleting during a walk invalidates the iterator the walk depends on. bounded so a fetch
     * that never errors cannot spin forever
     */
    while (n < ESP_NOW_MAX_TOTAL_PEER_NUM && esp_now_fetch_peer(true, &peer) == ESP_OK) {
        if (esp_now_del_peer(peer.peer_addr) != ESP_OK) {
            break;
        }
        ++n;
    }
PR00("peer table flushed: %d -> %d\n", pn.total_num, (esp_now_get_peer_num(&pn) == ESP_OK) ? pn.total_num : -1);
}
/* ---^^^--- crash forensics ---^^^---------------------------------------------------------------- */

#if !defined(NO_INITIATOR)

/*
 * a host zero string denotes the cmd wants to be sent to STD_TARGET_HOST via WiFi (and to the given non zero host otherwise)
 */
_i32
forward_cmd(_i8cp cmd, _i8cp host, _u16 port, _i8p *statmsg_p)
{
TP05
    _i8 stat = 0;
    ledact(1);
    lederr(1);

#if defined(RELAIS)         // existence implied 

/*
 * trigger on:
 * @beep=garage_toggle0 ^
 * @beep=garage_toggle1 ^
 * @beep=garage_toggle2 ^
 * @beep=garage_toggle3 ^
 */
#define CMD_TRIGGER_RELAIS "@beep=garage_toggle"

if (!strncmp(cmd, CMD_TRIGGER_RELAIS, strlen(CMD_TRIGGER_RELAIS))) {
    relact(1);
    vTaskDelay(pdMS_TO_TICKS(1000));
    relact(0);
}
#endif

    /*
     * the received data (see above) is a cmd and forwarded unmodified (aka with no trailing '\n')
     * to match historic mysend behavior
     */
    if (!mysend(cmd, host, port, statmsg_p)) {
        // nothin to do
    } else {
        stat = 1;
    }

    ledact(0);
    lederr(0);
    return stat;
}
#endif  // if !defined(NO_INITIATOR)

/*
 * see also rpi5:/root/bin/tcp_server
 */

// MUST MATCH host7 !! CHECK host7:/root/bin/tcp_server
/*
 *    SIMPLY TAKE THE COUNT OF OPENING BRACE AS NUMBER HERE:
 */
#define BR_CMD 1
#define BR_HOST 3
#define BR_PORT 7
#define BR_RETRIES 9
#define BR_SERIAL 11
#define BR_INSTSTAT 12

#define BR_PMATCH_INDX (BR_INSTSTAT + 1)                      // use last indx +1
#define BR_MATCHED(indx) (br_pmatch[(indx)].rm_so != -1)

_i32 br_regerr;
regex_t br_regex;
_i8 br_regbuf[128];
regmatch_t br_pmatch[BR_PMATCH_INDX];  // nr of parenthesized subexprs + 1

// all \ in bash (of tcp_server on host7) must be escaped twice \\ in C
// MUST MATCH host7 !! CHECK host7:/root/bin/tcp_server
_i8cp BR_CMD_MATCH = "^([^^]+)( \\^(([^^:0-9][^^:]+)|([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+))(:([0-9]+))?)?( \\^([0-9]+)R?)?( \\^([0-9]+)S)?( \\^)?$";
//                        |           |                                                       |                |                |          |
//                        BR_CMD      |                                                       |                |                |          |
//                        1           BR_HOST                                                 |                |                |          |
//                                    3                                                       BR_PORT          |                |          |
//                                                                                            7                BR_RETRIES       |          |
//                                                                                                             9                BR_SERIAL  |
//                                                                                                                              11         BR_INSTSTAT
//                                                                                                                                         12
 
/*
 * this macro is the ONLY thing between a 127-byte ESPNOW packet (ESPNOW_DATALEN) and the buffers
 * it fills, so the bound belongs here rather than in their declarations - six call sites, one
 * macro. strncat()'s n is the MATCH length and never the size of the destination, and the regex
 * caps neither BR_HOST nor BR_PORT nor BR_SERIAL, so before this "no ^<40-char host>" smashed the
 * frame from any sender in radio range. see regress/protocol/corpus.overflow in ~/esp.
 *
 * cv must be an ARRAY in scope: _SZ() is sizeof, so passing a pointer would silently bound the
 * copy at 4 bytes instead of the buffer size.
 *
 * the do/while is not cosmetic either - this used to be two statements with no wrapper, so
 * "if (x) BR_GET_CV_STR(a, b);" ran the copy unconditionally.
 *
 * memcpy + explicit terminator rather than strncat: every call site starts from an empty buffer,
 * so this was always a bounded COPY wearing an append's clothes. it also keeps -Wstringop-truncation
 * quiet, which fires (correctly) once the bound is visible - gcc reporting "between 0 and 31 bytes"
 * for host[32] was how the per-destination sizes got confirmed in the first place.
 *
 * BR_GET_CV_STR() usable even without preceding BR_MATCHED() because:
 *   strncat(cv, (_i8p)pkt.data - 1, -1 - -1) -> strncat(cv, (_i8p)pkt.data - 1, 0)
 * -> 
 *   results in null string
 */
#define BR_GET_CV_STR(cv, indx) \
do { \
    _i32 _so  = br_pmatch[(indx)].rm_so; \
    _i32 _len = _so < 0 ? 0 : br_pmatch[(indx)].rm_eo - _so;   /* unmatched -> null string, */ \
    if (_so < 0) _so = 0;                                      /* without forming data - 1   */ \
    if (_len > (_i32)_SZ(cv) - 1) _len = _SZ(cv) - 1; \
    memcpy((cv), (_i8p)espnow_unsol_pkt.data + _so, _len); \
    (cv)[_len] = 0; \
} while (0)

void 
espnow_unsol_task(void *arg)
{
TP05
    espnow_packet_t espnow_unsol_pkt;

    while (1) {
        if (xQueueReceive(espnow_unsol_que, &espnow_unsol_pkt, portMAX_DELAY)) {
#if DEBUG > 3
            /*
             * received data has no trailing '\n' but contains the terminating null / also reflected in espnow_unsol_pkt.len
             * e.g.:
             * received data: [@beep= f:1000 c:1 t:.05 p:.25 g:-20 ^host1 ^] len: 44 mac aa:bb:cc:00:00:0f
             */
            // the i.... does not handle _i8 as true signed char?! -> must cast to (signed char) explicitly 
            PR05("received ESPNOW cmd: [%s] len: %d src " MACSTR " -> dst " MACSTR " rssi %d" "\n", 
                                                    espnow_unsol_pkt.data, 
                                                    espnow_unsol_pkt.len, 
                                                    MAC2STR(espnow_unsol_pkt.src_mac), 
                                                    MAC2STR(espnow_unsol_pkt.dst_mac), 
                                                    (signed char)espnow_unsol_pkt.rssi);
#endif
            if (!memcmp(espnow_unsol_pkt.dst_mac, "\xff\xff\xff\xff\xff\xff", ESP_NOW_ETH_ALEN)) {
                PR05("ignoring broadcast packet\n");
                continue;
            }
            peer_flush_if_full();   // before the add, see there
            ESPNOW_ADD_PEER(espnow_unsol_pkt.src_mac);

#if defined(NO_INITIATOR)

#if DEBUG > 5
            PR05("pre ACKing ONLY with %s", STAT_OK);    // \n is contained in STAT_ already
#endif
            CK_SITE(CR_SITE_ACK_NOINI, esp_now_send(espnow_unsol_pkt.src_mac, (_u8p)STAT_OK, strlen(STAT_OK)));  // DO NOT copy terminating 0

#else // if defined(NO_INITIATOR)

            if (br_regerr = regexec(&br_regex, (_i8p)espnow_unsol_pkt.data, _NE(br_pmatch), br_pmatch, 0)) {
                // no match
                regerror(br_regerr, &br_regex, br_regbuf, _SZ(br_regbuf));
PR05("%s\n", br_regbuf);
            } else {

#if DEBUG > 8
                _i8 br_buf[128];
                for (_u32 i = 1; i < BR_PMATCH_INDX; ++i) {
                    BR_GET_CV_STR(br_buf, i);
                    PR05("BR %d: [%s]\n", i, br_buf);
                }
                BR_GET_CV_STR(br_buf, BR_CMD);
                PR05("BR_CMD: [%s]\n", br_buf);
                BR_GET_CV_STR(br_buf, BR_HOST);
                PR05("BR_HOST: [%s]\n", br_buf);
                BR_GET_CV_STR(br_buf, BR_PORT);
                PR05("BR_PORT: [%s]\n", br_buf);
                BR_GET_CV_STR(br_buf, BR_RETRIES);
                PR05("BR_RETRIES: [%s]\n", br_buf);
                BR_GET_CV_STR(br_buf, BR_SERIAL);
                PR05("BR_SERIAL: [%s]\n", br_buf);
                BR_GET_CV_STR(br_buf, BR_INSTSTAT);
                PR05("BR_INSTSTAT: [%s]\n", br_buf);
#endif
                /*
                 * ----------------------------------------------------------------
                 * what works:
                 *
                 *      - multi-antenna pre-acked cmds by tcp_server
                 *          { ESPNOW_SSID, ESPNOW_TARGET_HOST, ESPNOW_TARGET_PORT, "@beep= f:1000 c:1 t:.05 p:.25 g:-20 ^host1.example.com:8888 ^" } // <= pre-acked by tcp_server
                 *
                 *      - multi-antenna non-pre-acked cmds via non-tcp_server
                 *          { ESPNOW_SSID, ESPNOW_TARGET_HOST, ESPNOW_TARGET_PORT, "@beep= f:1000 c:1 t:.05 p:.25 g:-20 ^host1.example.com:8888" }   // <= directed to non-tcp_server
                 *
                 * what is NOT tested:
                 *
                 *      - multi-antenna non-pre-acked cmds via tcp_server
                 *          { ESPNOW_SSID, ESPNOW_TARGET_HOST, ESPNOW_TARGET_PORT, "@beep= f:1000 c:1 t:.05 p:.25 g:-20" }                     // <= NOT pre-acked by tcp_server
                 *
                 *      <== BUT NOT SUPPORTED ANYWAYS:
                 *          26-07-05 17:48:01 no valid p-cmd ^@beep= f:1000 c:1 t:.05 p:.25 g:-20^
                 *
                 * ----------------------------------------------------------------
                 *
                 * serial number/multi antenna gateway on non-pre-acked code path is widely UNTESTED!!!!!!!!!!!!!!!
                 *
                 * preliminary process behavior:        MAY BE FIXED IN THE FUTURE!!
                 *
                 * from bell you get the SAME benign status for a duplicate as for a real execution
                 *      <= nothing to ignore; bell drops the duplicate itself and answers 0/0 either
                 *         way, deliberately (see accept_close(.., 0) in bell.c). verified 2026_09_15
                 * from p    you get either stat: 5136 #[ii]#[0]#[0]#[xxx]#[0]#[0]                  <= if p received and duped it, or
                 *                              <=== SHOULD BE FIXED IN p!!!!!!
                 *                => status after forward_cmd(): <#[XX]#[0]#[0]#[xxx]#[0]#[0]
                 *      <= should be ignored but status not avail -> so can't detect -> indicate correct reception anyway -> so keep it
                 * from p    you get invalid read count and/or unterminated data statmsg: err#3     <= if p missed it
                 *                => status after forward_cmd(): <#[XX]#[0]#[0]#[xxx]#[err#3]#[1]
                 *      <= ignore these
                 * from p    you get ... socket connect failed errno=104 at 31326                   <= if p stopped
                 *                => status after forward_cmd(): <#[XX]#[0]#[0]#[xxx]#[err#2]#[1]
                 *      <= ignore these
                 *
                 * in multi antenna gateway mode we may not forward duplicate status to prevent clogging the
                 * one and only receive buffer on initiator side
                 *
                 * affected so far:
                 *
                 *  - EXPERIMENTAL: timeouts from p-process (can't handle multi cmds in parallel)
                 *
                 * ATTENTION!!!
                 * take care of other statuses coming from tcp_server like
                 *
                 *  
                 * echo '#[XX]#[0]#[0]#[xxx]#[0]#[1]'
                 * echo $0 "$_ARG" '-> busy, IGNORING' >&2
                 * exit 0
                 *  
                 * echo '#[XX]#[0]#[0]#[xxx]#[0]#[1]'
                 * echo $0 "$_ARG" '-> busy2, IGNORING' >&2
                 * exit 0
                 *
                 *      <= which of those are to forward/ignore?!?!?!?
                 *
                 *
                 *  THIS BRANCH (non pre-acked duplicates) IS USED for BELL.C ONLY ATM  ALL OTHERS ARE PRELIMINARY
                 *  THIS BRANCH (non pre-acked duplicates) IS USED for BELL.C ONLY ATM  ALL OTHERS ARE PRELIMINARY
                 *  THIS BRANCH (non pre-acked duplicates) IS USED for BELL.C ONLY ATM  ALL OTHERS ARE PRELIMINARY
                 *
                 * TEST WITH:   
                 *      ultra_remote_mini.c
                 *      
                 * test_case_t test_case[] = {}
                 * 
                 * { ESPNOW_SSID, ESPNOW_TARGET_HOST,     ESPNOW_TARGET_PORT, "@beep= f:1000 c:1 t:.05 p:.25 g:-20 ^host1.example.com:8888" },  // p-process does not work well with fast multi cmds in a row
                 * { ESPNOW_SSID, ESPNOW_TARGET_HOST,     ESPNOW_TARGET_PORT, "no ^host1.example.com:8899" },                                   // non-pre-acked, no req rel stat
                 * { ESPNOW_SSID, ESPNOW_TARGET_HOST,     ESPNOW_TARGET_PORT, "np ^host1.example.com:8899" },                                   // non-pre-acked, req rel stat
                 *
                 *
                 */

                _i8 cmd[128];
                _i8 host[32];
                _i8 port[16];
                _i8 retries[16];
                _i8 serial[16];
                _i8 status[128];
                _i8 inststat[8];
                _i8p statmsg;
                _i8 stat;

                BR_GET_CV_STR(cmd, BR_CMD);
                BR_GET_CV_STR(host, BR_HOST);
                BR_GET_CV_STR(port, BR_PORT);
                BR_GET_CV_STR(retries, BR_RETRIES);
                BR_GET_CV_STR(serial, BR_SERIAL);
                BR_GET_CV_STR(inststat, BR_INSTSTAT);

                /*
                 * rebuild what the TARGET still needs. host and port are consumed here - they
                 * become forward_cmd()'s destination - but retries and the serial-no are for
                 * tcp_server and have to travel with the command:
                 *
                 *   serial-no  filtered there, which is what makes multi-gateway dedup work
                 *   retries    becomes REXEC_MAXRETRIES, bounding its reconnect loop. it used to
                 *              be dropped here, so a "^20R" from a remote never arrived and every
                 *              command silently ran on tcp_server's default of 20 instead
                 *
                 * the order must match BR_CMD_MATCH: cmd, ^<retries>R, ^<serial>S, ^ - the parser
                 * at the far end is the same regex and will not match them out of order.
                 *
                 * built as two ready-made pieces rather than a walking cursor: snprintf returns
                 * what it WOULD have written, so "n += snprintf(...)" can step past the end and
                 * turn the next (_SZ(cmd) - n) into a huge size_t.
                 */
                _i8 r_part[20] = "";
                _i8 s_part[20] = "";

                if (*retries) snprintf(r_part, _SZ(r_part), " ^%sR", retries);
                if (*serial)  snprintf(s_part, _SZ(s_part), " ^%sS", serial);
                snprintf(cmd + strlen(cmd), _SZ(cmd) - strlen(cmd), "%s%s%s", r_part, s_part, inststat);

                // if either host or port is the null string -> resort to std host and port
#if defined(GW_TIMING_TRACE)
                /*
                 * queue wait is measured BEFORE forward_cmd, forward duration around it. the
                 * depth is read at the same moment: a non-zero depth here means a further command
                 * was already waiting while this one was still being forwarded, which is the
                 * contention the whole question is about - and the only direct evidence for it
                 */
                _u64 t_deq = esp_timer_get_time();
                _u32 q_wait = (_u32)(t_deq - espnow_unsol_pkt.t_rx);
                _u32 q_depth = uxQueueMessagesWaiting(espnow_unsol_que);
#endif
                stat = forward_cmd(cmd, !*host ? STD_TARGET_HOST : host, !*port ? STD_TARGET_PORT : atoi(port), &statmsg);
#if defined(GW_TIMING_TRACE)
                _u32 fwd = (_u32)(esp_timer_get_time() - t_deq);
PR01("GWTIME q%luus f%luus d%lu\n", (unsigned long)q_wait, (unsigned long)fwd, (unsigned long)q_depth);
#endif
                /*
                 * statmsg points at mcom.h's stat_misc_buf[128], so 21 chars of prefix + up to
                 * 127 + 6 of suffix overflowed status[128]. reachable through the ordinary path:
                 * send a cmd pq.bash does not know and tcp_server echoes it back inside
                 * "no valid p-cmd ^...^"
                 */
#if defined(GW_TIMING_TRACE)
                /*
                 * ride the numbers home in status field 4. STATUS_MATCH constrains it to
                 * [a-z0-9]+ (it is the literal "xxx" otherwise) and the remote reads only fields
                 * 5 and 6, so this is free carriage - and it arrives already correlated with the
                 * exact exchange, which a separate log on a board with no USB cable would not.
                 *
                 * q = queue wait us, f = forward_cmd us, d = queue depth at dequeue, g = entity
                 */
                /*
                 * c/w/r split forward_cmd's time across mysend()'s three TCP phases, taken at the
                 * existing WTPROF boundaries in mcom.h:
                 *   c  socket + connect (incl. any FAST CONNECT RETRY rounds)
                 *   w  the write of the command
                 *   r  the read that blocks until tcp_server emits the pre-ack  <- the suspect
                 * f still covers all of forward_cmd, so f - (c+w+r) is everything outside the
                 * socket work - DNS/cache lookup and the ledact/lederr bracket
                 */
                /*
                 * s<serial> makes the trace SELF-IDENTIFYING, and it is not optional.
                 *
                 * the status carries no serial of its own, and mysend() on the remote clears
                 * espnow_sol_pkt.len then accepts the first frame that turns up - so a straggler
                 * from the PREVIOUS command (the two losing gateways each send one, 10..40ms
                 * behind the winner) is accepted as this command's status. for pre-acked commands
                 * every status is an identical "0/0" so nothing downstream notices, but it made
                 * 36%% of the first timing run's rows report a forward longer than the whole round
                 * trip. echoing the serial back lets the analysis drop exactly those rows
                 */
                _i8 tr[80];
                snprintf(tr, _SZ(tr), "q%luf%luc%luw%lur%lud%lug%ds%s",
                    (unsigned long)q_wait, (unsigned long)fwd,
                    (unsigned long)gw_t_connect, (unsigned long)gw_t_write, (unsigned long)gw_t_read,
                    (unsigned long)q_depth, ENTITY, *serial ? serial : "0");
                snprintf(status, _SZ(status), "#[XX]#[0]#[0]#[%s]#[%s]#[%d]\n", tr, statmsg, stat);
#elif defined(GW_SERIAL_ECHO)
                _i8 tr[24];
                snprintf(tr, _SZ(tr), "g%ds%s", ENTITY, *serial ? serial : "0");
                snprintf(status, _SZ(status), "#[XX]#[0]#[0]#[%s]#[%s]#[%d]\n", tr, statmsg, stat);
#else
                snprintf(status, _SZ(status), "#[XX]#[0]#[0]#[xxx]#[%s]#[%d]\n", statmsg, stat);
#endif

#if 0   // HACK obsoleted as of 2026_09_16/ due to system-related limitations p-process is no longer a multi gateway supported target 
                /*
                 * HACK ALERT: wrong fix to the right problem
                 *
                 * p-processes immanently can't handle multiple concurrent connections required for multi gateway setups.
                 * so we drop a status if it's an "err#3" due to compatibility reasons.
                 * an "err#3" is always issued faster than a good status eventually trailing will be delivered.
                 * this keeps room in the single receive buffer for good statuses eventually trailing behind.
                 * a real "err#3" on all connections would timeout the receiver anyway mitigating the hack to some extend.
                 */
                if (!*serial
                 || !stat
                 || strcmp(statmsg, "err#3")) {
#endif
                    CK_SITE(CR_SITE_STATUS, esp_now_send(espnow_unsol_pkt.src_mac, (_u8p)status, strlen(status)));  // DO NOT copy terminating 0
                    PR02("returning status: <%s>\n", status);
#if 0
                } else {
                    PR05("dropping err#3 as duplicate status\n");
                }
#endif
            }
#endif  // !defined(NO_INITIATOR)
        }
    }
}

// ======================================== provide a service control port ========================================
#if defined(MYSERVICE_PORT)

#define RESTART_GRACE_PERIOD 700        // allow sending status et.al.

#define SET_INDX 1
#define GET_INDX 3
#define OTA_INDX 4
#define BOOT_INDX 5
#define ON_INDX  6
#define OFF_INDX 7

#define PMATCH_INDX (OFF_INDX + 1)                      // use last indx +1
#define MATCHED(indx) (pmatch[(indx)].rm_so != -1)

_i32 regerr;
_i8 regbuf[128];
_i8cp CMD_MATCH =
     \
    "^@([^ =]+)=([^ =]+)$" "|" \
    "^@([^ =]+)$"          "|" \
    "^(OTA)$"              "|" \
    "^(BOOT)$"              "|" \
    "^(ON)$"               "|" \
    "^(OFF)$"                  \
    ;
regex_t regex;
regmatch_t pmatch[PMATCH_INDX];  // nr of parenthesized subexprs + 1

/*
 * bounded by cv as well as by the match: the regex caps no field and a line may run to BUF_SIZE,
 * so a long @name or value would otherwise be copied past the end of cmd[]/val[] on the stack
 */
#define GET_CV_STR(cv, indx) \
    *cv = 0; strncat(cv, buf + pmatch[(indx)].rm_so, min((size_t)(pmatch[(indx)].rm_eo - pmatch[(indx)].rm_so), _SZ(cv) - 1));

#define GET_MISC_STR(misc) \
    crash_misc_str(misc, _SZ(misc))

#define BUF_SIZE 256    // for buf[], must also hold statusStr (cmd + misc + some)
#define RECV_TIMEOUT 1  // x 1s, the stream timeout arduino's readStringUntil() gave up after

#define CONTINUE(str) \
    PR05("Error: " str); \
    vTaskDelay(pdMS_TO_TICKS(1000)); \
    continue;

void 
myserv_task(void *arg)
{
TP05
    _i32 listen_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = _SZ(client_addr);
    _i8 buf[BUF_SIZE];

    while (1) {
        listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (listen_sock < 0) {
            CONTINUE("unable to create socket\n");
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(MYSERVICE_PORT);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(listen_sock, (struct sockaddr *)&server_addr, _SZ(server_addr)) < 0) {
            close(listen_sock);
            CONTINUE("socket bind failed\n");
        }
        if (listen(listen_sock, 1) < 0) {
            close(listen_sock);
            CONTINUE("listen failed\n");
        }
        PR05("listening on port %d\n", MYSERVICE_PORT);
        while (1) {
            addr_len = _SZ(client_addr);
            client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &addr_len);
            if (client_sock < 0) {
                close(listen_sock);
                PR05("Error: accept failed\n");
                vTaskDelay(pdMS_TO_TICKS(1000));
                break;      // to a fresh listen socket - a CONTINUE here would accept() on the closed one forever
            }
ledact(1);
            PR05("new client connected\n");
            struct timeval tv = { .tv_sec = RECV_TIMEOUT, .tv_usec = 0 };   // a client that never sends must not hold the port
            setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, _SZ(tv));

            _i32 total = 0;
            while (1) {
                _i32 len = recv(client_sock, buf + total, 1, 0);
                if (len <= 0) { // gets terminated per \0
                    PR05("client disconnected prematurely\n");
                    break;
                }
                if (buf[total] == '\n') { // gets over patched per \0
                    break;
                }
                total++;
                if (total >= BUF_SIZE - 1) { // gets terminated per \0
                    break;
                }
            }
            buf[total] = 0;

            _i8 cmd[64];
            _i8 val[64];
            _i8 misc[96];   // crash_misc_str() needs the room, see there
            _u8 stat = 0;
            PR05("<%s>\n", buf);
            if (regerr = regexec(&regex, buf, _NE(pmatch), pmatch, 0)) {
                // no match
                regerror(regerr, &regex, regbuf, _SZ(regbuf));
PR05("%s\n", regbuf);
                sprintf(cmd, "ILLEG regex");
                stat = 1;
            } else if (MATCHED(OTA_INDX)) {
                GET_CV_STR(cmd, OTA_INDX);
            } else if (MATCHED(GET_INDX)) {
                GET_CV_STR(cmd, GET_INDX);
                if (!strcmp(cmd, "state")) {
                } else {
PR05("[ %s ] does not exist\n", cmd);
                    sprintf(cmd, "ERR get");
                    stat = 1;
                }
            } else if (MATCHED(SET_INDX)) {
                GET_CV_STR(cmd, SET_INDX);
                GET_CV_STR(val, SET_INDX + 1);
                if (!strcmp(cmd, "state_RO")) {
                    // nothing to do ATM
                } else {
PR05("[ %s ] does not exist\n", cmd);
                    sprintf(cmd, "ERR set");
                    stat = 1;
                }
            } else if (MATCHED(BOOT_INDX)) {
                GET_CV_STR(cmd, BOOT_INDX);
            } else if (MATCHED(ON_INDX)) {
                GET_CV_STR(cmd, ON_INDX);
            } else if (MATCHED(OFF_INDX)) {
                GET_CV_STR(cmd, OFF_INDX);
            } else {
PR05("illegal cmd\n");
                sprintf(cmd, "ILLEG cmd");
                stat = 1;
            }
            GET_MISC_STR(misc);
            statusStr(cmd, stat, misc, buf, _SZ(buf));
            send(client_sock, buf, strlen(buf), 0);
            close(client_sock);
            PR05("client disconnected\n");
ledact(0);
            /*
             * delay execution to allow sending status in advance
             */
            if (!strcmp(cmd, "OTA")) {
                auto_upgrade_FW(1);                                 // in forced mode we must always reboot
                vTaskDelay(pdMS_TO_TICKS(RESTART_GRACE_PERIOD));    // allow sending status
                esp_restart();                                      // hardware has been touched -> we reboot
            } else if (!strcmp(cmd, "BOOT")) {
                vTaskDelay(pdMS_TO_TICKS(RESTART_GRACE_PERIOD));         // allow sending status
                esp_restart();  
            } else if (!strcmp(cmd, "ON")) {
PR05("cut_off_power(1)\n");
            } else if (!strcmp(cmd, "OFF")) {
PR05("cut_off_power(0)\n");
            }
        }
    } // while
}
#endif  // defined(MYSERVICE_PORT)

#if defined(CONNECTIVITY_WATCHOG)
// --- vvv -------------------------- network watchdog for IDE ----------------------------------
#include "ping/ping_sock.h"

void 
ping_success_cb(esp_ping_handle_t hdl, void *args)
{
TP05
    _i32 *ok = (_i32 *)args;
    *ok = 1;
}

_i32 
ping_gateway(u32_t gate_ip)
{
TP05
    esp_ping_config_t config = ESP_PING_DEFAULT_CONFIG();

    config.target_addr.addr = gate_ip;
    config.count = 1;
    config.timeout_ms = 100;
    _i32 success = 0;

    esp_ping_callbacks_t cbs = {
        .on_ping_success = ping_success_cb,
        .on_ping_timeout = NULL,
        .on_ping_end = NULL,
        .cb_args = &success
    };

    esp_ping_handle_t ping;
    esp_ping_new_session(&config, &cbs, &ping);
    esp_ping_start(ping);
    vTaskDelay(pdMS_TO_TICKS(150));  // wait for result
    esp_ping_stop(ping);
    esp_ping_delete_session(ping);

    return success;
}

#define PING_INTERVAL 10000
//#define __HARD_RECONNECT_VERSION__

void
wifi_watchdog_task(void *arg)
{
TP05
    u32_t saved_gw = 0;

    while (1) {
        if (!saved_gw) {
            if (*gw_ip && strcmp(gw_ip, "0")) {
                PR05("save gw [%s]--------------------------------------------------\n", gw_ip);
                saved_gw = ipaddr_addr(gw_ip);
            } else {
                PR05("gw not yet saved----------------------------------------------\n");
            }
        } else {
            if (!ping_gateway(saved_gw)) {

#if !defined(__HARD_RECONNECT_VERSION__)

                PR05("Network dead → now reconnect----------------------------------\n");
                esp_wifi_disconnect();
                vTaskDelay(pdMS_TO_TICKS(500));
                esp_wifi_connect();

#else   // if !defined(__HARD_RECONNECT_VERSION__)

                PR05("Network dead → now reboot-------------------------------------\n");
                vTaskDelay(pdMS_TO_TICKS(2000));
                __i32 skip_fw_update = 0;
                SET_NVS(skip_fw_update, 1); // hack to avoid FW upgrade attempt
                esp_restart();
#endif  // if !defined(__HARD_RECONNECT_VERSION__)

            }
        }
        vTaskDelay(pdMS_TO_TICKS(PING_INTERVAL));
    }
}
// --- ^^^ -------------------------- network watchdog for IDE ----------------------------------
#endif //if defined(CONNECTIVITY_WATCHOG)

void
app_main()
{
TP05
    crash_log_boot();   // before anything else here can crash - see crash forensics above
    init_1st();
    init_2nd();
    if (auto_upgrade_FW(0)) {
        esp_restart(); // if the hardware has been touched we reboot
    }
#if defined(RELAIS) || defined(LED_PIN1) || defined(LED_PIN2)
    gpio_config_t io_conf = { 0 };
    io_conf.mode = GPIO_MODE_OUTPUT;
#if defined(RELAIS)
    io_conf.pin_bit_mask |= (_u64)1 << RELAIS;
#endif
#if defined(LED_PIN1)
    io_conf.pin_bit_mask |= (_u64)1 << LED_PIN1;
#endif
#if defined(LED_PIN2)
    io_conf.pin_bit_mask |= (_u64)1 << LED_PIN2;
#endif
    gpio_config(&io_conf);

    relact(0);
    ledact(0);
    lederr(0);
#endif  // if defined(RELAIS) || defined(LED_PIN1) || defined(LED_PIN2)

    // analyze ESPNOW cmd to be forwarded as specified
    if (br_regerr = regcomp(&br_regex, BR_CMD_MATCH, REG_EXTENDED)) {
        regerror(br_regerr, &br_regex, br_regbuf, _SZ(br_regbuf));
        PR05("%s\n", br_regbuf);
    }
#if defined(MYSERVICE_PORT)
    // analyze cmd received on service port
    if (regerr = regcomp(&regex, CMD_MATCH, REG_EXTENDED)) {
        regerror(regerr, &regex, regbuf, _SZ(regbuf));
        PR05("%s\n", regbuf);
    }
    xTaskCreate(myserv_task, "tcp_server", 4096, NULL, 5, NULL);
#endif
#if defined(ETH_INITIATOR)
    PR05("working as ESPNOW -> ETH forwarder\n");
    if (init_eth(ETH_WORKS_AS_DHCP_CLIENT, 1)) {
        PR05("could not ETH_MODE client eth lan8720\n");
    }
    ESPNOW_WIFI_SETUP();
#elif defined(NO_INITIATOR)
    PR05("working as ESPNOW standalone server\n");
    ESPNOW_WIFI_SETUP();
#else
    PR05("working as ESPNOW -> WiFi forwarder\n");
    /*
     * this section is only relevant for ESPNOW -> WiFi forwarders (others are handled above under ETH_INITIATOR)
     *
     * full blown ur_connect() replaces ESPNOW_WIFI_SETUP()
     *
     * take care as SSID change implies channel change probebly
     * which impacts clients also!!!!!!!!!!!!!!!!
     */
#if ESP32_(37)  // # esp32-37 192.168.0.11  aa:bb:cc:00:00:01   ultra_espnow_gw/       seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #3 botland (host13 garage)
    if (ur_connect(UFIRE_SSID, WIFI_CONN_WAIT, WIFI_CONN_SLOW_FAIL, WIFI_PS_NONE)) {
#else           // # esp32-44 192.168.0.12   aa:bb:cc:00:00:03   ultra_espnow_gw/       seed studio XIAO ESP32-S3 8 MB PSRAM/ 8 MB Flash #1 botland (media room) + ALL OTHERS
    if (ur_connect(ROTA2K_SSID, WIFI_CONN_WAIT, WIFI_CONN_SLOW_FAIL, WIFI_PS_NONE)) { // }
#endif  // ESP32_(37) USY WIFI / OWN WIFI
        PR05("can't ur_connect, rebooting...\n");
        esp_restart();
    }
#endif  // defined(ETH_INITIATOR) NO_INITIATOR/ WIFI_INITIATOR
    ESPNOW_INIT();
#if defined(CONNECTIVITY_WATCHOG)
    xTaskCreate(wifi_watchdog_task, "wifi_watchdog_task", 4096, NULL, 5, NULL);
#endif
    PR05("ESPNOW gateway ready\n");

#if defined(CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE)
    /*
     * everything that could strand this device has now succeeded: the uplink is up (ur_connect()
     * for the WiFi gateways, init_eth() for the eth ones - both esp_restart() on failure above),
     * the tasks are running and ESPNOW is initialised. only now is the image worth keeping.
     *
     * without this call the bootloader leaves a freshly OTA'd image in ESP_OTA_IMG_PENDING_VERIFY
     * and reverts to the previous app on the next boot. that is exactly the safety net these
     * devices need: esp32-44/75/79 have no serial line in their final positions, so an image that
     * fails to come up currently means physically fetching the device. an image that cannot reach
     * this line now reverts itself instead.
     *
     * NOT under ESP_ERROR_CHECK: on an ordinary boot we are not in PENDING_VERIFY at all and the
     * call returns an error by design - aborting on that would brick every normal boot
     */
    {
        esp_err_t rb = esp_ota_mark_app_valid_cancel_rollback();
        /*
         * PR00 and not PR05: these entities build with DEBUG 1, so PR05 constant folds to nothing
         * and the whole line disappears - which is exactly why the gateways are silent. this one
         * has to be visible, it is how we see whether the image kept itself or is about to revert
         */
PR00("ota mark valid: %s\n", rb == ESP_OK ? "ok" : esp_err_to_name(rb));
    }
#endif
}

