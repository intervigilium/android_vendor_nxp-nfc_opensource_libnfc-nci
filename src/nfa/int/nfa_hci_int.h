/******************************************************************************
 *  Copyright (c) 2016, The Linux Foundation. All rights reserved.
 *  Not a Contribution.
 *
 *  Copyright (C) 2015 NXP Semiconductors
 *  The original Work has been changed by NXP Semiconductors.
 *
 *  Copyright (C) 2010-2014 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This is the private interface file for the NFA HCI.
 *
 ******************************************************************************/
#ifndef NFA_HCI_INT_H
#define NFA_HCI_INT_H

#include "nfa_hci_api.h"

extern BOOLEAN HCI_LOOPBACK_DEBUG;
#if((NXP_EXTNS == TRUE) && (NXP_NFCC_MW_RCVRY_BLK_FW_DNLD == TRUE))
BOOLEAN MW_RCVRY_FW_DNLD_ALLOWED;
#endif
/*****************************************************************************
**  Constants and data types
*****************************************************************************/


#define NFA_HCI_HOST_ID_UICC0           0x02        /* Host ID for UICC 0 */
#define NFA_HCI_LAST_HOST_SPECIFIC_GATE 0xEF        /* Lost host specific gate */

#define NFA_HCI_SESSION_ID_LEN          8           /* HCI Session ID length */
#define NFA_MAX_PIPES_IN_GENERIC_GATE   0x0F        /* Maximum pipes that can be created on a generic pipe  */

#if (NXP_EXTNS == TRUE)
#define NFA_HCI_HOST_TYPE_LEN          2           /* HCI Host Type length */
#define NFA_HCI_CONTROLLER_VERSION_9   9           /* HCI controller ETSI Version 9 */
#define NFA_HCI_CONTROLLER_VERSION_12  12          /* HCI controller ETSI Version 12 */
#define NFA_HCI_HOST_ID_UICC1          0x81        /* Host ID for UICC 1 */
#define NFA_HCI_HOST_ID_ESE            0xC0        /* Host ID for ESE    */
#define NFA_HCI_SESSION_ID_MASK        0x0100      /* Bit Mask to indicate session ID poll is done or not*/
#define NFA_HCI_NFCEE_CONFIG_MASK      0x0200      /* Bit mask to indicate ETSI12 config done or not*/
#define NFA_HCI_SET_CONFIG_EVENT       0x01        /* event to set the nfcee config bit*/
#define NFA_HCI_CLEAR_CONFIG_EVENT     0x02        /* event to clear the nfcee config bit*/
#endif


#define NFA_HCI_VERSION_SW              0x090000    /* HCI SW Version number                       */
#define NFA_HCI_VERSION_HW              0x000000    /* HCI HW Version number                       */
#define NFA_HCI_VENDOR_NAME             "HCI"       /* Vendor Name                                 */
#define NFA_HCI_MODEL_ID                00          /* Model ID                                    */
#define NFA_HCI_VERSION                 90          /* HCI Version                                 */

/* NFA HCI states */
#define NFA_HCI_STATE_DISABLED              0x00     /* HCI is disabled  */
#define NFA_HCI_STATE_STARTUP               0x01     /* HCI performing Initialization sequence */
#define NFA_HCI_STATE_WAIT_NETWK_ENABLE     0x02     /* HCI is waiting for initialization of other host in the network */
#define NFA_HCI_STATE_IDLE                  0x03     /* HCI is waiting to handle api commands  */
#define NFA_HCI_STATE_WAIT_RSP              0x04     /* HCI is waiting for response to command sent */
#define NFA_HCI_STATE_REMOVE_GATE           0x05     /* Removing all pipes prior to removing the gate */
#define NFA_HCI_STATE_APP_DEREGISTER        0x06     /* Removing all pipes and gates prior to deregistering the app */
#define NFA_HCI_STATE_RESTORE               0x07     /* HCI restore */
#define NFA_HCI_STATE_RESTORE_NETWK_ENABLE  0x08     /* HCI is waiting for initialization of other host in the network after restore */
#if(NXP_EXTNS == TRUE)
#define NFA_HCI_STATE_NFCEE_ENABLE          0x09     /* HCI is waiting for NFCEE initialization */
#endif

#if(NXP_EXTNS == TRUE)
#define NFA_HCI_MAX_RSP_WAIT_TIME               0x0C
#define NFA_HCI_CHAIN_PKT_RSP_TIMEOUT           30000    /* After the reception of WTX, maximum response timeout value is 30 sec */
#define NFA_HCI_WTX_RESP_TIMEOUT                3000     /* Wait time to give response timeout to application if WTX not received*/
#define NFA_HCI_DWP_RSP_WAIT_TIMEOUT            2000     /* time out for wired mode response after RF deativation */
#define NFA_HCI_DWP_SESSION_ABORT_TIMEOUT       5000     /* time out for wired session aborted(0xE6 ntf) due to SWP switched to UICC*/
#define NFA_HCI_SESSION_ID_POLL_DELAY           50       /* delay between session ID poll to check if the reset host is initilized or not */
#define NFA_HCI_MAX_SESSION_ID_RETRY_CNT        0x0A     /* retry count for session ID poll*/
#define NFA_HCI_NFCEE_DISC_TIMEOUT              0x02     /* NFCEE disc timeout default value in sec*/
/*  NXP specific events */
#define NFA_HCI_GET_NUM_NFCEE_CONFIGURED        0xF1     /* Event to read the number of NFCEE configured in NFCC*/
#define NFA_HCI_READ_SESSIONID                  0xF2     /* Event to read the session ID of all the Secure Element*/
#define NFA_HCI_INIT_NFCEE_CONFIG               0xF3     /* Event to start ETSI 12 configuration*/
#define NFA_HCI_NFCEE_CONFIG_COMPLETE           0xF9     /* NFCEE ETSI 12 configuration complete*/
#endif

typedef UINT8 tNFA_HCI_STATE;

/* NFA HCI PIPE states */
#define NFA_HCI_PIPE_CLOSED             0x00     /* Pipe is closed */
#define NFA_HCI_PIPE_OPENED             0x01     /* Pipe is opened */

#define NFA_HCI_INVALID_INX             0xFF


typedef UINT8 tNFA_HCI_COMMAND;
typedef UINT8 tNFA_HCI_RESPONSE;


/* NFA HCI Internal events */
enum
{
    NFA_HCI_API_REGISTER_APP_EVT = NFA_SYS_EVT_START (NFA_ID_HCI),/* Register APP with HCI */
    NFA_HCI_API_DEREGISTER_APP_EVT,                               /* Deregister an app from HCI */
    NFA_HCI_API_GET_APP_GATE_PIPE_EVT,                            /* Get the list of gate and pipe associated to the application */
    NFA_HCI_API_ALLOC_GATE_EVT,                                   /* Allocate a dyanmic gate for the application */
    NFA_HCI_API_DEALLOC_GATE_EVT,                                 /* Deallocate a previously allocated gate to the application */
    NFA_HCI_API_GET_HOST_LIST_EVT,                                /* Get the list of Host in the network */
    NFA_HCI_API_GET_REGISTRY_EVT,                                 /* Get a registry entry from a host */
    NFA_HCI_API_SET_REGISTRY_EVT,                                 /* Set a registry entry on a host */
    NFA_HCI_API_CREATE_PIPE_EVT,                                  /* Create a pipe between two gates */
    NFA_HCI_API_OPEN_PIPE_EVT,                                    /* Open a pipe */
    NFA_HCI_API_CLOSE_PIPE_EVT,                                   /* Close a pipe */
    NFA_HCI_API_DELETE_PIPE_EVT,                                  /* Delete a pipe */
    NFA_HCI_API_ADD_STATIC_PIPE_EVT,                              /* Add a static pipe */
    NFA_HCI_API_SEND_CMD_EVT,                                     /* Send command via pipe */
    NFA_HCI_API_SEND_RSP_EVT,                                     /* Application Response to a command */
#if(NXP_EXTNS == TRUE)
    NFA_HCI_API_CONFIGURE_EVT,                                    /* Configure NFCEE as per ETSI 12 standards */
#endif
    NFA_HCI_API_SEND_EVENT_EVT,                                   /* Send event via pipe */

    NFA_HCI_RSP_NV_READ_EVT,                                      /* Non volatile read complete event */
    NFA_HCI_RSP_NV_WRITE_EVT,                                     /* Non volatile write complete event */
    NFA_HCI_RSP_TIMEOUT_EVT,                                      /* Timeout to response for the HCP Command packet */
    NFA_HCI_CHECK_QUEUE_EVT
#if(NXP_EXTNS == TRUE)
    ,NFA_HCI_SESSION_ID_POLL_DELAY_TIMEOUT_EVT                    /*timeout event to read session id on timeout*/
    ,NFA_HCI_NFCEE_DISCOVER_TIMEOUT_EVT                           /*timeout event for waiting for all configured nfcee to be discovered*/
#endif
};

#define NFA_HCI_FIRST_API_EVENT     NFA_HCI_API_REGISTER_APP_EVT
#define NFA_HCI_LAST_API_EVENT      NFA_HCI_API_SEND_EVENT_EVT

typedef UINT16 tNFA_HCI_INT_EVT;

/* Internal event structures.
**
** Note, every internal structure starts with a BT_HDR and an app handle
*/

/* data type for NFA_HCI_API_REGISTER_APP_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    char                app_name[NFA_MAX_HCI_APP_NAME_LEN + 1];
    tNFA_HCI_CBACK      *p_cback;
    BOOLEAN             b_send_conn_evts;
} tNFA_HCI_API_REGISTER_APP;

/* data type for NFA_HCI_API_DEREGISTER_APP_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    char                app_name[NFA_MAX_HCI_APP_NAME_LEN + 1];
} tNFA_HCI_API_DEREGISTER_APP;

/* data type for NFA_HCI_API_GET_APP_GATE_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
} tNFA_HCI_API_GET_APP_GATE_PIPE;

/* data type for NFA_HCI_API_ALLOC_GATE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               gate;
} tNFA_HCI_API_ALLOC_GATE;

/* data type for NFA_HCI_API_DEALLOC_GATE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               gate;
} tNFA_HCI_API_DEALLOC_GATE;

/* data type for NFA_HCI_API_GET_HOST_LIST_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
} tNFA_HCI_API_GET_HOST_LIST;

/* data type for NFA_HCI_API_GET_REGISTRY_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               pipe;
    UINT8               reg_inx;
} tNFA_HCI_API_GET_REGISTRY;

/* data type for NFA_HCI_API_SET_REGISTRY_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               pipe;
    UINT8               reg_inx;
    UINT8               size;
    UINT8               data[NFA_MAX_HCI_CMD_LEN];
} tNFA_HCI_API_SET_REGISTRY;

/* data type for NFA_HCI_API_CREATE_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
    UINT8               source_gate;
    UINT8               dest_host;
    UINT8               dest_gate;
} tNFA_HCI_API_CREATE_PIPE_EVT;

/* data type for NFA_HCI_API_OPEN_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
    UINT8               pipe;
} tNFA_HCI_API_OPEN_PIPE_EVT;

/* data type for NFA_HCI_API_CLOSE_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
    UINT8               pipe;
} tNFA_HCI_API_CLOSE_PIPE_EVT;

/* data type for NFA_HCI_API_DELETE_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
    UINT8               pipe;
} tNFA_HCI_API_DELETE_PIPE_EVT;

/* data type for NFA_HCI_API_ADD_STATIC_PIPE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    tNFA_STATUS         status;
    UINT8               host;
    UINT8               gate;
    UINT8               pipe;
} tNFA_HCI_API_ADD_STATIC_PIPE_EVT;

/* data type for NFA_HCI_API_SEND_EVENT_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               pipe;
    UINT8               evt_code;
    UINT16              evt_len;
    UINT8               *p_evt_buf;
    UINT16              rsp_len;
    UINT8               *p_rsp_buf;
#if(NXP_EXTNS == TRUE)
    UINT32              rsp_timeout;
#else
    UINT16              rsp_timeout;
#endif
} tNFA_HCI_API_SEND_EVENT_EVT;

#if(NXP_EXTNS == TRUE)
/* data type for tNFA_HCI_API_CONFIGURE_EVT */
typedef struct
{
    BT_HDR              hdr;
    UINT16              config_nfcee_event;
} tNFA_HCI_API_CONFIGURE_EVT;

typedef UINT16 tNFA_CONFIG_STATE;
#endif

/* data type for NFA_HCI_API_SEND_CMD_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               pipe;
    UINT8               cmd_code;
    UINT16              cmd_len;
    UINT8               data[NFA_MAX_HCI_CMD_LEN];
} tNFA_HCI_API_SEND_CMD_EVT;

/* data type for NFA_HCI_RSP_NV_READ_EVT */
typedef struct
{
    BT_HDR              hdr;
    UINT8               block;
    UINT16              size;
    tNFA_STATUS         status;
} tNFA_HCI_RSP_NV_READ_EVT;

/* data type for NFA_HCI_RSP_NV_WRITE_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_STATUS         status;
} tNFA_HCI_RSP_NV_WRITE_EVT;

/* data type for NFA_HCI_API_SEND_RSP_EVT */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
    UINT8               pipe;
    UINT8               response;
    UINT8               size;
    UINT8               data[NFA_MAX_HCI_RSP_LEN];
} tNFA_HCI_API_SEND_RSP_EVT;

/* common data type for internal events */
typedef struct
{
    BT_HDR              hdr;
    tNFA_HANDLE         hci_handle;
} tNFA_HCI_COMM_DATA;

/* union of all event data types */
typedef union
{
    BT_HDR                              hdr;
    tNFA_HCI_COMM_DATA                  comm;

    /* API events */
    tNFA_HCI_API_REGISTER_APP           app_info;                       /* Register/Deregister an application */
    tNFA_HCI_API_GET_APP_GATE_PIPE      get_gate_pipe_list;             /* Get the list of gates and pipes created for the application */
    tNFA_HCI_API_ALLOC_GATE             gate_info;                      /* Allocate a dynamic gate to the application */
    tNFA_HCI_API_DEALLOC_GATE           gate_dealloc;                   /* Deallocate the gate allocated to the application */
    tNFA_HCI_API_CREATE_PIPE_EVT        create_pipe;                    /* Create a pipe */
    tNFA_HCI_API_OPEN_PIPE_EVT          open_pipe;                      /* Open a pipe */
    tNFA_HCI_API_CLOSE_PIPE_EVT         close_pipe;                     /* Close a pipe */
    tNFA_HCI_API_DELETE_PIPE_EVT        delete_pipe;                    /* Delete a pipe */
    tNFA_HCI_API_ADD_STATIC_PIPE_EVT    add_static_pipe;                /* Add a static pipe */
    tNFA_HCI_API_GET_HOST_LIST          get_host_list;                  /* Get the list of Host in the network */
    tNFA_HCI_API_GET_REGISTRY           get_registry;                   /* Get a registry entry on a host */
    tNFA_HCI_API_SET_REGISTRY           set_registry;                   /* Set a registry entry on a host */
    tNFA_HCI_API_SEND_CMD_EVT           send_cmd;                       /* Send a event on a pipe to a host */
    tNFA_HCI_API_SEND_RSP_EVT           send_rsp;                       /* Response to a command sent on a pipe to a host */
    tNFA_HCI_API_SEND_EVENT_EVT         send_evt;                       /* Send a command on a pipe to a host */

    /* Internal events */
    tNFA_HCI_RSP_NV_READ_EVT            nv_read;                        /* Read Non volatile data */
    tNFA_HCI_RSP_NV_WRITE_EVT           nv_write;                       /* Write Non volatile data */

#if (NXP_EXTNS == TRUE)
    tNFA_HCI_API_CONFIGURE_EVT          config_info;                    /* Configuration of NFCEE for ETSI12 */
#endif
} tNFA_HCI_EVENT_DATA;

/*****************************************************************************
**  control block
*****************************************************************************/

/* Dynamic pipe control block */
typedef struct
{
    UINT8                   pipe_id;                /* Pipe ID */
    tNFA_HCI_PIPE_STATE     pipe_state;             /* State of the Pipe */
    UINT8                   local_gate;             /* local gate id */
    UINT8                   dest_host;              /* Peer host to which this pipe is connected */
    UINT8                   dest_gate;              /* Peer gate to which this pipe is connected */
} tNFA_HCI_DYN_PIPE;

/* Dynamic gate control block */
typedef struct
{
    UINT8                   gate_id;                /* local gate id */
    tNFA_HANDLE             gate_owner;             /* NFA-HCI handle assigned to the application which owns the gate */
    UINT32                  pipe_inx_mask;          /* Bit 0 == pipe inx 0, etc */
} tNFA_HCI_DYN_GATE;

/* Admin gate control block */
typedef struct
{
    tNFA_HCI_PIPE_STATE pipe01_state;                       /* State of Pipe '01' */
    UINT8               session_id[NFA_HCI_SESSION_ID_LEN]; /* Session ID of the host network */
} tNFA_ADMIN_GATE_INFO;

/* Link management gate control block */
typedef struct
{
    tNFA_HCI_PIPE_STATE pipe00_state;               /* State of Pipe '00' */
    UINT16              rec_errors;                 /* Receive errors */
} tNFA_LINK_MGMT_GATE_INFO;

/* Identity management gate control block */
typedef struct
{
    UINT32              pipe_inx_mask;                  /* Bit 0 == pipe inx 0, etc */
    UINT16              version_sw;                     /* Software version number */
    UINT16              version_hw;                     /* Hardware version number */
    UINT8               vendor_name[20];                /* Vendor name */
    UINT8               model_id;                       /* Model ID */
    UINT8               hci_version;                    /* HCI Version */
} tNFA_ID_MGMT_GATE_INFO;

/* Internal flags */
#define NFA_HCI_FL_DISABLING        0x01                /* sub system is being disabled */
#define NFA_HCI_FL_NV_CHANGED       0x02                /* NV Ram changed */
#if (NXP_EXTNS == TRUE)
#define NFA_HCI_FL_CONN_PIPE        0x01
#define NFA_HCI_FL_APDU_PIPE        0x02
#define NFA_HCI_FL_OTHER_PIPE       0x04
#define NFA_HCI_CONN_UICC_PIPE      0x0A
#define NFA_HCI_CONN_ESE_PIPE       0x16
#define NFA_HCI_APDU_PIPE           0x19
#define NFA_HCI_CONN_UICC2_PIPE     0x23                /*Connectivity pipe no of UICC2*/
#define NFA_HCI_INIT_MAX_RETRY      20
#endif
/* NFA HCI control block */
typedef struct
{
    tNFA_HCI_STATE                  hci_state;                          /* state of the HCI */
    UINT8                           num_nfcee;                          /* Number of NFCEE ID Discovered */
    UINT8                           num_ee_dis_req_ntf;                 /* Number of ee discovery request ntf received */
    UINT8                           num_hot_plug_evts;                  /* Number of Hot plug events received after ee discovery disable ntf */
    UINT8                           inactive_host[NFA_HCI_MAX_HOST_IN_NETWORK]; /* Inactive host in the host network */
    UINT8                           reset_host[NFA_HCI_MAX_HOST_IN_NETWORK]; /* List of host reseting */
    BOOLEAN                         b_low_power_mode;                   /* Host controller in low power mode */
    BOOLEAN                         b_hci_netwk_reset;                  /* Command sent to reset HCI Network */
    BOOLEAN                         w4_hci_netwk_init;                  /* Wait for other host in network to initialize */
    TIMER_LIST_ENT                  timer;                              /* Timer to avoid indefinitely waiting for response */
    UINT8                           conn_id;                            /* Connection ID */
    UINT8                           buff_size;                          /* Connection buffer size */
    BOOLEAN                         nv_read_cmplt;                      /* NV Read completed */
    BOOLEAN                         nv_write_needed;                    /* Something changed - NV write is needed */
    BOOLEAN                         assembling;                         /* Set true if in process of assembling a message  */
    BOOLEAN                         assembly_failed;                    /* Set true if Insufficient buffer to Reassemble incoming message */
    BOOLEAN                         w4_rsp_evt;                         /* Application command sent on HCP Event */
    tNFA_HANDLE                     app_in_use;                         /* Index of the application that is waiting for response */
    UINT8                           local_gate_in_use;                  /* Local gate currently working with */
    UINT8                           remote_gate_in_use;                 /* Remote gate currently working with */
    UINT8                           remote_host_in_use;                 /* The remote host to which a command is sent */
    UINT8                           pipe_in_use;                        /* The pipe currently working with */
    UINT8                           param_in_use;                       /* The registry parameter currently working with */
    tNFA_HCI_COMMAND                cmd_sent;                           /* The last command sent */
    BOOLEAN                         ee_disc_cmplt;                      /* EE Discovery operation completed */
    BOOLEAN                         ee_disable_disc;                    /* EE Discovery operation is disabled */
    UINT16                          msg_len;                            /* For segmentation - length of the combined message */
    UINT16                          max_msg_len;                        /* Maximum reassembled message size */
    UINT8                           msg_data[NFA_MAX_HCI_EVENT_LEN];    /* For segmentation - the combined message data */
    UINT8                           *p_msg_data;                        /* For segmentation - reassembled message */
#if (NXP_EXTNS == TRUE)
    UINT8                           assembling_flags;                   /* the flags to keep track of assembling status*/
    UINT8                           assembly_failed_flags;              /* the flags to keep track of failed assembly*/
    UINT8                           *p_evt_data;                        /* For segmentation - reassembled event data */
    UINT16                          evt_len;                            /* For segmentation - length of the combined event data */
    UINT16                          max_evt_len;                        /* Maximum reassembled message size */
    UINT8                           evt_data[NFA_MAX_HCI_EVENT_LEN];    /* For segmentation - the combined event data */
    UINT8                           type_evt;                               /* Instruction type of incoming message */
    UINT8                           inst_evt;                               /* Instruction of incoming message */
    UINT8                           type_msg;                               /* Instruction type of incoming message */
    UINT8                           inst_msg;                               /* Instruction of incoming message */
    UINT8                           host_count;                             /* no of Hosts ETSI 12 compliant */
    UINT8                           host_id[NFA_HCI_MAX_NO_HOST_ETSI12];    /* Host id ETSI 12 compliant */
    UINT8                           host_controller_version;                 /* no of host controller version */
    UINT8                           current_nfcee;                      /* current Nfcee under execution  */
    BOOLEAN                         IsHciTimerChanged;
    BOOLEAN                         IsWiredSessionAborted;
    UINT32                          hciResponseTimeout;
    BOOLEAN                         IsChainedPacket;
    BOOLEAN                         bIsHciResponseTimedout;
    UINT16                          hci_packet_len;
    BOOLEAN                         IsEventAbortSent;
    BOOLEAN                         IsLastEvtAbortFailed;
    tNFA_HCI_EVENT_SENT             evt_sent;
    struct
    {
        tNFA_CONFIG_STATE           config_nfcee_state;                  /*state change during config nfcee handling*/
        UINT8                       session_id_retry;                    /*retry count for session ID*/
        tNFA_HANDLE                 host_cb[NFA_HCI_MAX_HOST_IN_NETWORK];/*host_cb which stores information on config complete ,session ID poll and other information*/
        BOOLEAN                     discovery_stopped;                   /*discovery stopped during config nfcee process*/
        BOOLEAN                     nfc_init_state;             /*handling clear all pipe*/
    }nfcee_cfg;

    UINT32                          max_hci_session_id_read_count;       /*Count for maximum  session id retry value */
    UINT32                          max_nfcee_disc_timeout;              /*Config file timeout value for all the NFCEE to be discovered */
    tNFA_EE_INFO                    hci_ee_info[NFA_HCI_MAX_HOST_IN_NETWORK];
#endif
    UINT8                           type;                               /* Instruction type of incoming message */
    UINT8                           inst;                               /* Instruction of incoming message */

    BUFFER_Q                        hci_api_q;                          /* Buffer Q to hold incoming API commands */
    BUFFER_Q                        hci_host_reset_api_q;               /* Buffer Q to hold incoming API commands to a host that is reactivating */
    tNFA_HCI_CBACK                  *p_app_cback[NFA_HCI_MAX_APP_CB];   /* Callback functions registered by the applications */
    UINT16                          rsp_buf_size;                       /* Maximum size of APDU buffer */
    UINT8                           *p_rsp_buf;                         /* Buffer to hold response to sent event */
    struct                                                              /* Persistent information for Device Host */
    {
        char                        reg_app_names[NFA_HCI_MAX_APP_CB][NFA_MAX_HCI_APP_NAME_LEN + 1];

        tNFA_HCI_DYN_GATE           dyn_gates[NFA_HCI_MAX_GATE_CB];
        tNFA_HCI_DYN_PIPE           dyn_pipes[NFA_HCI_MAX_PIPE_CB];

        BOOLEAN                     b_send_conn_evts[NFA_HCI_MAX_APP_CB];
        tNFA_ADMIN_GATE_INFO        admin_gate;
        tNFA_LINK_MGMT_GATE_INFO    link_mgmt_gate;
        tNFA_ID_MGMT_GATE_INFO      id_mgmt_gate;
#if (NXP_EXTNS == TRUE)
        UINT8                       retry_cnt;
#endif
    } cfg;

} tNFA_HCI_CB;


/*****************************************************************************
**  External variables
*****************************************************************************/

/* NFA HCI control block */
#if NFA_DYNAMIC_MEMORY == FALSE
extern tNFA_HCI_CB nfa_hci_cb;
#else
extern tNFA_HCI_CB *nfa_hci_cb_ptr;
#define nfa_hci_cb (*nfa_hci_cb_ptr)
#endif


/*****************************************************************************
**  External functions
*****************************************************************************/

/* Functions in nfa_hci_main.c
*/
extern void nfa_hci_init (void);
extern void nfa_hci_proc_nfcc_power_mode (UINT8 nfcc_power_mode);
extern void nfa_hci_dh_startup_complete (void);
extern void nfa_hci_startup_complete (tNFA_STATUS status);
extern void nfa_hci_startup (void);
extern void nfa_hci_restore_default_config (UINT8 *p_session_id);
#if (NXP_EXTNS == TRUE)
extern void nfa_hci_release_transcieve();
extern void nfa_hci_network_enable();
extern tNFA_STATUS nfa_hciu_reset_session_id(tNFA_VSC_CBACK *p_cback);
extern tNFA_STATUS nfa_hciu_send_raw_cmd(UINT8 param_len, UINT8* p_data, tNFA_VSC_CBACK   *p_cback);
extern BOOLEAN nfa_hciu_check_nfcee_poll_done(UINT8 host_id);
extern BOOLEAN nfa_hciu_check_nfcee_config_done(UINT8 host_id);
extern void nfa_hciu_set_nfceeid_config_mask(UINT8 event, UINT8 host_id);
extern void nfa_hciu_set_nfceeid_poll_mask(UINT8 event, UINT8 host_id);
extern BOOLEAN nfa_hciu_check_any_host_reset_pending();
extern tNFA_STATUS nfa_hci_api_config_nfcee (UINT8 hostId);
#if (NXP_UICC_HANDLE_CLEAR_ALL_PIPES == TRUE)
void nfa_hci_handle_clear_all_pipes_evt(UINT8 source_host);
#endif
#endif

/* Action functions in nfa_hci_act.c
*/
extern void nfa_hci_check_pending_api_requests (void);
extern void nfa_hci_check_api_requests (void);
extern void nfa_hci_handle_admin_gate_cmd (UINT8 *p_data);
extern void nfa_hci_handle_admin_gate_rsp (UINT8 *p_data, UINT8 data_len);
extern void nfa_hci_handle_admin_gate_evt (UINT8 *p_data);
extern void nfa_hci_handle_link_mgm_gate_cmd (UINT8 *p_data);
extern void nfa_hci_handle_dyn_pipe_pkt (UINT8 pipe, UINT8  *p_data, UINT16 data_len);
extern void nfa_hci_handle_pipe_open_close_cmd (tNFA_HCI_DYN_PIPE *p_pipe);
extern void nfa_hci_api_dealloc_gate (tNFA_HCI_EVENT_DATA *p_evt_data);
extern void nfa_hci_api_deregister (tNFA_HCI_EVENT_DATA *p_evt_data);

/* Utility functions in nfa_hci_utils.c
*/
extern tNFA_HCI_DYN_GATE  *nfa_hciu_alloc_gate (UINT8 gate_id, tNFA_HANDLE app_handle);
extern tNFA_HCI_DYN_GATE  *nfa_hciu_find_gate_by_gid (UINT8 gate_id);
extern tNFA_HCI_DYN_GATE  *nfa_hciu_find_gate_by_owner (tNFA_HANDLE app_handle);
extern tNFA_HCI_DYN_GATE  *nfa_hciu_find_gate_with_nopipes_by_owner (tNFA_HANDLE app_handle);
extern tNFA_HCI_DYN_PIPE  *nfa_hciu_find_pipe_by_pid (UINT8 pipe_id);
extern tNFA_HCI_DYN_PIPE  *nfa_hciu_find_pipe_by_owner (tNFA_HANDLE app_handle);
extern tNFA_HCI_DYN_PIPE  *nfa_hciu_find_active_pipe_by_owner (tNFA_HANDLE app_handle);
extern tNFA_HCI_DYN_PIPE  *nfa_hciu_find_pipe_on_gate (UINT8 gate_id);
extern tNFA_HANDLE         nfa_hciu_get_gate_owner (UINT8 gate_id);
extern BOOLEAN             nfa_hciu_check_pipe_between_gates (UINT8 local_gate, UINT8 dest_host, UINT8 dest_gate);
extern BOOLEAN             nfa_hciu_is_active_host (UINT8 host_id);
extern BOOLEAN             nfa_hciu_is_host_reseting (UINT8 host_id);
extern BOOLEAN             nfa_hciu_is_no_host_resetting (void);
extern tNFA_HCI_DYN_PIPE  *nfa_hciu_find_active_pipe_on_gate (UINT8 gate_id);
extern tNFA_HANDLE         nfa_hciu_get_pipe_owner (UINT8 pipe_id);
extern UINT8               nfa_hciu_count_open_pipes_on_gate (tNFA_HCI_DYN_GATE *p_gate);
extern UINT8               nfa_hciu_count_pipes_on_gate (tNFA_HCI_DYN_GATE *p_gate);
extern tNFA_STATUS         nfa_hciu_asmbl_dyn_pipe_pkt (UINT8 *p_data, UINT8 data_len);

extern tNFA_HCI_RESPONSE   nfa_hciu_add_pipe_to_gate (UINT8 pipe, UINT8 local_gate, UINT8 dest_host, UINT8 dest_gate);
extern tNFA_HCI_RESPONSE   nfa_hciu_add_pipe_to_static_gate (UINT8 local_gate, UINT8 pipe_id, UINT8 dest_host, UINT8 dest_gate);

extern tNFA_HCI_RESPONSE   nfa_hciu_release_pipe (UINT8 pipe_id);
extern void                nfa_hciu_release_gate (UINT8 gate);
extern void                nfa_hciu_remove_all_pipes_from_host (UINT8 host);
extern UINT8               nfa_hciu_get_allocated_gate_list (UINT8 *p_gate_list);

extern void                nfa_hciu_send_to_app (tNFA_HCI_EVT event, tNFA_HCI_EVT_DATA *p_evt, tNFA_HANDLE app_handle);
extern void                nfa_hciu_send_to_all_apps (tNFA_HCI_EVT event, tNFA_HCI_EVT_DATA *p_evt);
extern void                nfa_hciu_send_to_apps_handling_connectivity_evts (tNFA_HCI_EVT event, tNFA_HCI_EVT_DATA *p_evt);

extern tNFA_STATUS nfa_hciu_send_close_pipe_cmd (UINT8 pipe);
extern tNFA_STATUS nfa_hciu_send_delete_pipe_cmd (UINT8 pipe);
extern tNFA_STATUS nfa_hciu_send_clear_all_pipe_cmd (void);
extern tNFA_STATUS nfa_hciu_send_open_pipe_cmd (UINT8 pipe);
extern tNFA_STATUS nfa_hciu_send_get_param_cmd (UINT8 pipe, UINT8 index);
extern tNFA_STATUS nfa_hciu_send_create_pipe_cmd (UINT8 source_gate, UINT8 dest_host, UINT8 dest_gate);
extern tNFA_STATUS nfa_hciu_send_set_param_cmd (UINT8 pipe, UINT8 index, UINT8 length, UINT8 *p_data);
extern tNFA_STATUS nfa_hciu_send_msg (UINT8 pipe_id, UINT8 type, UINT8 instruction, UINT16 pkt_len, UINT8 *p_pkt);



#if (BT_TRACE_VERBOSE == TRUE)
extern char *nfa_hciu_type_2_str (UINT8 type);
extern char *nfa_hciu_instr_2_str (UINT8 type);
extern char *nfa_hciu_get_event_name (UINT16 event);
extern char *nfa_hciu_get_response_name (UINT8 rsp_code);
extern char *nfa_hciu_get_state_name (UINT8 state);
extern char *nfa_hciu_get_type_inst_names (UINT8 pipe, UINT8 type, UINT8 inst, char *p_buff);
extern char *nfa_hciu_evt_2_str (UINT8 pipe_id, UINT8 evt);
#define VERBOSE_BUFF_SIZE 100
#endif


#endif /* NFA_HCI_INT_H */
