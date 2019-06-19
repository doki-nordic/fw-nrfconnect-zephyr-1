/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CERTIFICATE_H__
#define __CERTIFICATE_H__

#define SERVER_CERTIFICATE_TAG 1
#define RSA_SERVER_CERTIFICATE_TAG 2
#define PSK_SERVER_CREDENTIALS_TAG 3

static const unsigned char server_certificate[] = {
#include "echo-apps-cert.der.inc"
};

/* This is the private key in pkcs#8 format. */
static const unsigned char private_key[] = {
#include "echo-apps-key.der.inc"
};

static const unsigned char rsa_server_certificate[] = {
#include "RSA-echo-apps-cert.der.inc"
};

/* This is the private key in pkcs#8 format. */
static const unsigned char rsa_private_key[] = {
#include "RSA-echo-apps-key.der.inc"
};

#endif /* __CERTIFICATE_H__ */
