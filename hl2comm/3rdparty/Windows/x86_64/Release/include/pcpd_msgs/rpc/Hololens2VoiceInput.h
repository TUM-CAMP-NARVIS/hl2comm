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
 * @file Hololens2VoiceInput.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_PCPD_MSGS_RPC_HOLOLENS2VOICEINPUT_H_
#define _FAST_DDS_GENERATED_PCPD_MSGS_RPC_HOLOLENS2VOICEINPUT_H_

#include "pcpd_msgs/rpc/Types.h"

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
#if defined(Hololens2VoiceInput_SOURCE)
#define Hololens2VoiceInput_DllAPI __declspec( dllexport )
#else
#define Hololens2VoiceInput_DllAPI __declspec( dllimport )
#endif // Hololens2VoiceInput_SOURCE
#else
#define Hololens2VoiceInput_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define Hololens2VoiceInput_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace pcpd_msgs {
    namespace rpc {
        /*!
         * @brief This class represents the structure HL2VIVoiceInput_Result defined by the user in the IDL file.
         * @ingroup HOLOLENS2VOICEINPUT
         */
        class HL2VIVoiceInput_Result
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport HL2VIVoiceInput_Result();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~HL2VIVoiceInput_Result();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIVoiceInput_Result that will be copied.
             */
            eProsima_user_DllExport HL2VIVoiceInput_Result(
                    const HL2VIVoiceInput_Result& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIVoiceInput_Result that will be copied.
             */
            eProsima_user_DllExport HL2VIVoiceInput_Result(
                    HL2VIVoiceInput_Result&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIVoiceInput_Result that will be copied.
             */
            eProsima_user_DllExport HL2VIVoiceInput_Result& operator =(
                    const HL2VIVoiceInput_Result& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIVoiceInput_Result that will be copied.
             */
            eProsima_user_DllExport HL2VIVoiceInput_Result& operator =(
                    HL2VIVoiceInput_Result&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIVoiceInput_Result object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const HL2VIVoiceInput_Result& x) const;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIVoiceInput_Result object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const HL2VIVoiceInput_Result& x) const;

            /*!
             * @brief This function sets a value in member index
             * @param _index New value for member index
             */
            eProsima_user_DllExport void index(
                    uint32_t _index);

            /*!
             * @brief This function returns the value of member index
             * @return Value of member index
             */
            eProsima_user_DllExport uint32_t index() const;

            /*!
             * @brief This function returns a reference to member index
             * @return Reference to member index
             */
            eProsima_user_DllExport uint32_t& index();

            /*!
             * @brief This function sets a value in member confidence
             * @param _confidence New value for member confidence
             */
            eProsima_user_DllExport void confidence(
                    uint32_t _confidence);

            /*!
             * @brief This function returns the value of member confidence
             * @return Value of member confidence
             */
            eProsima_user_DllExport uint32_t confidence() const;

            /*!
             * @brief This function returns a reference to member confidence
             * @return Reference to member confidence
             */
            eProsima_user_DllExport uint32_t& confidence();

            /*!
             * @brief This function sets a value in member phrase_duration
             * @param _phrase_duration New value for member phrase_duration
             */
            eProsima_user_DllExport void phrase_duration(
                    uint64_t _phrase_duration);

            /*!
             * @brief This function returns the value of member phrase_duration
             * @return Value of member phrase_duration
             */
            eProsima_user_DllExport uint64_t phrase_duration() const;

            /*!
             * @brief This function returns a reference to member phrase_duration
             * @return Reference to member phrase_duration
             */
            eProsima_user_DllExport uint64_t& phrase_duration();

            /*!
             * @brief This function sets a value in member phrase_start_time
             * @param _phrase_start_time New value for member phrase_start_time
             */
            eProsima_user_DllExport void phrase_start_time(
                    uint64_t _phrase_start_time);

            /*!
             * @brief This function returns the value of member phrase_start_time
             * @return Value of member phrase_start_time
             */
            eProsima_user_DllExport uint64_t phrase_start_time() const;

            /*!
             * @brief This function returns a reference to member phrase_start_time
             * @return Reference to member phrase_start_time
             */
            eProsima_user_DllExport uint64_t& phrase_start_time();

            /*!
             * @brief This function sets a value in member raw_confidence
             * @param _raw_confidence New value for member raw_confidence
             */
            eProsima_user_DllExport void raw_confidence(
                    double _raw_confidence);

            /*!
             * @brief This function returns the value of member raw_confidence
             * @return Value of member raw_confidence
             */
            eProsima_user_DllExport double raw_confidence() const;

            /*!
             * @brief This function returns a reference to member raw_confidence
             * @return Reference to member raw_confidence
             */
            eProsima_user_DllExport double& raw_confidence();


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
                    const pcpd_msgs::rpc::HL2VIVoiceInput_Result& data,
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

            uint32_t m_index;
            uint32_t m_confidence;
            uint64_t m_phrase_duration;
            uint64_t m_phrase_start_time;
            double m_raw_confidence;

        };
        /*!
         * @brief This class represents the structure HL2VIRequest_RegisterCommands defined by the user in the IDL file.
         * @ingroup HOLOLENS2VOICEINPUT
         */
        class HL2VIRequest_RegisterCommands
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport HL2VIRequest_RegisterCommands();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~HL2VIRequest_RegisterCommands();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIRequest_RegisterCommands that will be copied.
             */
            eProsima_user_DllExport HL2VIRequest_RegisterCommands(
                    const HL2VIRequest_RegisterCommands& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIRequest_RegisterCommands that will be copied.
             */
            eProsima_user_DllExport HL2VIRequest_RegisterCommands(
                    HL2VIRequest_RegisterCommands&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIRequest_RegisterCommands that will be copied.
             */
            eProsima_user_DllExport HL2VIRequest_RegisterCommands& operator =(
                    const HL2VIRequest_RegisterCommands& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIRequest_RegisterCommands that will be copied.
             */
            eProsima_user_DllExport HL2VIRequest_RegisterCommands& operator =(
                    HL2VIRequest_RegisterCommands&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIRequest_RegisterCommands object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const HL2VIRequest_RegisterCommands& x) const;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIRequest_RegisterCommands object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const HL2VIRequest_RegisterCommands& x) const;

            /*!
             * @brief This function sets a value in member clear
             * @param _clear New value for member clear
             */
            eProsima_user_DllExport void clear(
                    bool _clear);

            /*!
             * @brief This function returns the value of member clear
             * @return Value of member clear
             */
            eProsima_user_DllExport bool clear() const;

            /*!
             * @brief This function returns a reference to member clear
             * @return Reference to member clear
             */
            eProsima_user_DllExport bool& clear();

            /*!
             * @brief This function copies the value in member commands
             * @param _commands New value to be copied in member commands
             */
            eProsima_user_DllExport void commands(
                    const std::vector<std::string>& _commands);

            /*!
             * @brief This function moves the value in member commands
             * @param _commands New value to be moved in member commands
             */
            eProsima_user_DllExport void commands(
                    std::vector<std::string>&& _commands);

            /*!
             * @brief This function returns a constant reference to member commands
             * @return Constant reference to member commands
             */
            eProsima_user_DllExport const std::vector<std::string>& commands() const;

            /*!
             * @brief This function returns a reference to member commands
             * @return Reference to member commands
             */
            eProsima_user_DllExport std::vector<std::string>& commands();

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
                    const pcpd_msgs::rpc::HL2VIRequest_RegisterCommands& data,
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

            bool m_clear;
            std::vector<std::string> m_commands;

        };
        /*!
         * @brief This class represents the structure HL2VIResponse_VoiceInput_Pop defined by the user in the IDL file.
         * @ingroup HOLOLENS2VOICEINPUT
         */
        class HL2VIResponse_VoiceInput_Pop
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport HL2VIResponse_VoiceInput_Pop();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~HL2VIResponse_VoiceInput_Pop();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop that will be copied.
             */
            eProsima_user_DllExport HL2VIResponse_VoiceInput_Pop(
                    const HL2VIResponse_VoiceInput_Pop& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop that will be copied.
             */
            eProsima_user_DllExport HL2VIResponse_VoiceInput_Pop(
                    HL2VIResponse_VoiceInput_Pop&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop that will be copied.
             */
            eProsima_user_DllExport HL2VIResponse_VoiceInput_Pop& operator =(
                    const HL2VIResponse_VoiceInput_Pop& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop that will be copied.
             */
            eProsima_user_DllExport HL2VIResponse_VoiceInput_Pop& operator =(
                    HL2VIResponse_VoiceInput_Pop&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const HL2VIResponse_VoiceInput_Pop& x) const;

            /*!
             * @brief Comparison operator.
             * @param x pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const HL2VIResponse_VoiceInput_Pop& x) const;

            /*!
             * @brief This function copies the value in member results
             * @param _results New value to be copied in member results
             */
            eProsima_user_DllExport void results(
                    const std::vector<pcpd_msgs::rpc::HL2VIVoiceInput_Result>& _results);

            /*!
             * @brief This function moves the value in member results
             * @param _results New value to be moved in member results
             */
            eProsima_user_DllExport void results(
                    std::vector<pcpd_msgs::rpc::HL2VIVoiceInput_Result>&& _results);

            /*!
             * @brief This function returns a constant reference to member results
             * @return Constant reference to member results
             */
            eProsima_user_DllExport const std::vector<pcpd_msgs::rpc::HL2VIVoiceInput_Result>& results() const;

            /*!
             * @brief This function returns a reference to member results
             * @return Reference to member results
             */
            eProsima_user_DllExport std::vector<pcpd_msgs::rpc::HL2VIVoiceInput_Result>& results();
            /*!
             * @brief This function sets a value in member status
             * @param _status New value for member status
             */
            eProsima_user_DllExport void status(
                    pcpd_msgs::rpc::RPCResponseStatus _status);

            /*!
             * @brief This function returns the value of member status
             * @return Value of member status
             */
            eProsima_user_DllExport pcpd_msgs::rpc::RPCResponseStatus status() const;

            /*!
             * @brief This function returns a reference to member status
             * @return Reference to member status
             */
            eProsima_user_DllExport pcpd_msgs::rpc::RPCResponseStatus& status();


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
                    const pcpd_msgs::rpc::HL2VIResponse_VoiceInput_Pop& data,
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

            std::vector<pcpd_msgs::rpc::HL2VIVoiceInput_Result> m_results;
            pcpd_msgs::rpc::RPCResponseStatus m_status;

        };
    } // namespace rpc
} // namespace pcpd_msgs

#endif // _FAST_DDS_GENERATED_PCPD_MSGS_RPC_HOLOLENS2VOICEINPUT_H_