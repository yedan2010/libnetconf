/**
 * \file messages.h
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief Internal functions to create NETCONF messages.
 *
 * Copyright (C) 2012 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef MESSAGES_INTERNAL_H_
#define MESSAGES_INTERNAL_H_

#include "netconf_internal.h"
#include "with_defaults.h"

/**
 * @brief Create the client \<hello\> message.
 * @ingroup internalAPI
 * @param caps List of client capabilities.
 * @return rpc structure with the created client \<hello\> message.
 */
nc_rpc *nc_msg_client_hello(char **caps);

/**
 * @brief Create the server \<hello\> message.
 * @ingroup internalAPI
 * @param caps List of server capabilities.
 * @param session_id Generated NETCONF session ID string.
 * @return rpc structure with the created server \<hello\> message.
 */
nc_rpc *nc_msg_server_hello(char **cpblts, char* session_id);

/**
 * @brief Get the message id string from the NETCONF message
 *
 * @param[in] msg NETCONF message to parse.
 * @return 0 on error,\n message-id of the message on success.
 */
const nc_msgid nc_msg_parse_msgid(const struct nc_msg *msg);

/**
 * @brief Parse a RPC message to get the type of RPC. The result value is also
 * stored in an internal RPC structure.
 *
 * @param[in] rpc RPC message to parse.
 * @return The type of the RPC.
 */
NC_RPC_TYPE nc_rpc_parse_type(nc_rpc* rpc);

/**
 * @brief Parse RPC-reply message to get the type of RPC-reply. The result
 * value is also stored in an internal rpc-reply structure.
 *
 * @param[in] reply RPC-reply message to parse.
 * @return The type of the RPC-reply.
 */
NC_REPLY_TYPE nc_reply_parse_type(nc_reply* reply);

/**
 * @brief Parse rpc and get with-defaults mode
 * @param[in] rpc NETCONF rpc message to be parsed
 * @return one of the with-defaults mode, 0 (NCDFLT_MODE_DISABLED) if not set
 */
NCWD_MODE nc_rpc_parse_withdefaults(nc_rpc* rpc, const struct nc_session* session);

/**
 * @ingroup internalAPI
 * @brief Create the <close-session> NETCONF rpc message.
 *
 * @return Created rpc message.
 */
nc_rpc *nc_rpc_closesession();

/**
 * @brief Create a generic NETCONF message envelope according to the given type
 * (rpc or rpc-reply) and insert the given data
 *
 * @param[in] content pointer to the xml node containing data
 * @param[in] msgtype string of the envelope element (rpc, rpc-reply)
 *
 * @return Prepared nc_msg structure.
 */
struct nc_msg* nc_msg_create(xmlNodePtr content, char* msgtype);

/**
 * @brief Free a generic message.
 * @param[in] msg Message to free.
 */
void nc_msg_free(struct nc_msg *msg);

/**
 * @brief Duplicate a message.
 * @param[in] msg Message to duplicate.
 * @return The copy of the given NETCONF message.
 */
struct nc_msg *nc_msg_dup(struct nc_msg *msg);

#endif /* MESSAGES_INTERNAL_H_ */
