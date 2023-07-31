// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file TFMessage.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_TF2_MSGS_MSG_TFMESSAGE_H_
#define _FAST_DDS_GENERATED_TF2_MSGS_MSG_TFMESSAGE_H_

#include "geometry_msgs/msg/TransformStamped.h"

#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(TFMessage_SOURCE)
#define TFMessage_DllAPI __declspec( dllexport )
#else
#define TFMessage_DllAPI __declspec( dllimport )
#endif // TFMessage_SOURCE
#else
#define TFMessage_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define TFMessage_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace tf2_msgs {
    namespace msg {
        /*!
         * @brief This class represents the structure TFMessage defined by the user in the IDL file.
         * @ingroup TFMESSAGE
         */
        class TFMessage
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport TFMessage();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~TFMessage();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object tf2_msgs::msg::TFMessage that will be copied.
             */
            eProsima_user_DllExport TFMessage(
                    const TFMessage& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object tf2_msgs::msg::TFMessage that will be copied.
             */
            eProsima_user_DllExport TFMessage(
                    TFMessage&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object tf2_msgs::msg::TFMessage that will be copied.
             */
            eProsima_user_DllExport TFMessage& operator =(
                    const TFMessage& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object tf2_msgs::msg::TFMessage that will be copied.
             */
            eProsima_user_DllExport TFMessage& operator =(
                    TFMessage&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x tf2_msgs::msg::TFMessage object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const TFMessage& x) const;

            /*!
             * @brief Comparison operator.
             * @param x tf2_msgs::msg::TFMessage object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const TFMessage& x) const;

            /*!
             * @brief This function copies the value in member transforms
             * @param _transforms New value to be copied in member transforms
             */
            eProsima_user_DllExport void transforms(
                    const std::vector<geometry_msgs::msg::TransformStamped>& _transforms);

            /*!
             * @brief This function moves the value in member transforms
             * @param _transforms New value to be moved in member transforms
             */
            eProsima_user_DllExport void transforms(
                    std::vector<geometry_msgs::msg::TransformStamped>&& _transforms);

            /*!
             * @brief This function returns a constant reference to member transforms
             * @return Constant reference to member transforms
             */
            eProsima_user_DllExport const std::vector<geometry_msgs::msg::TransformStamped>& transforms() const;

            /*!
             * @brief This function returns a reference to member transforms
             * @return Reference to member transforms
             */
            eProsima_user_DllExport std::vector<geometry_msgs::msg::TransformStamped>& transforms();

            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const tf2_msgs::msg::TFMessage& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            std::vector<geometry_msgs::msg::TransformStamped> m_transforms;

        };
    } // namespace msg
} // namespace tf2_msgs

#endif // _FAST_DDS_GENERATED_TF2_MSGS_MSG_TFMESSAGE_H_