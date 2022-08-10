/*
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2017 - 2018 Intel Corporation.
 * All Rights Reserved.
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Intel Corporation
 * or licensors. Title to the Material remains with Intel
 * Corporation or its licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No License under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials, either expressly, by implication, inducement,
 * estoppel or otherwise. Any license under such intellectual property rights
 * must be express and approved by Intel in writing.
 */

#ifndef __IPU_DEVICE_PIFCONV_CTRL_PROPERTIES_H
#define __IPU_DEVICE_PIFCONV_CTRL_PROPERTIES_H

#include "storage_class.h"

enum pifconv_type {
	PIFCONV_TYPE_A,
	PIFCONV_TYPE_B
};

STORAGE_CLASS_INLINE unsigned int
ipu_device_pifconv_ctrl_base_addr(const unsigned int pifconv_ctrl_dev);

STORAGE_CLASS_INLINE enum pifconv_type
ipu_device_pifconv_ctrl_type(const unsigned int pifconv_ctrl_dev);

#include "ipu_device_pifconv_ctrl_properties_func.h"

#endif /*__IPU_DEVICE_PIFCONV_CTRL_PROPERTIES_H*/