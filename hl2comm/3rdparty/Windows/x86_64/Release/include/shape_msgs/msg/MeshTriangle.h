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
 * @file MeshTriangle.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_SHAPE_MSGS_MSG_MESHTRIANGLE_H_
#define _FAST_DDS_GENERATED_SHAPE_MSGS_MSG_MESHTRIANGLE_H_


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
#if defined(MeshTriangle_SOURCE)
#define MeshTriangle_DllAPI __declspec( dllexport )
#else
#define MeshTriangle_DllAPI __declspec( dllimport )
#endif // MeshTriangle_SOURCE
#else
#define MeshTriangle_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define MeshTriangle_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace shape_msgs {
    namespace msg {
        typedef std::array<uint32_t, 3> uint32__3;
        /*!
         * @brief This class represents the structure MeshTriangle defined by the user in the IDL file.
         * @ingroup MESHTRIANGLE
         */
        class MeshTriangle
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport MeshTriangle();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~MeshTriangle();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object shape_msgs::msg::MeshTriangle that will be copied.
             */
            eProsima_user_DllExport MeshTriangle(
                    const MeshTriangle& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object shape_msgs::msg::MeshTriangle that will be copied.
             */
            eProsima_user_DllExport MeshTriangle(
                    MeshTriangle&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object shape_msgs::msg::MeshTriangle that will be copied.
             */
            eProsima_user_DllExport MeshTriangle& operator =(
                    const MeshTriangle& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object shape_msgs::msg::MeshTriangle that will be copied.
             */
            eProsima_user_DllExport MeshTriangle& operator =(
                    MeshTriangle&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x shape_msgs::msg::MeshTriangle object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const MeshTriangle& x) const;

            /*!
             * @brief Comparison operator.
             * @param x shape_msgs::msg::MeshTriangle object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const MeshTriangle& x) const;

            /*!
             * @brief This function copies the value in member vertex_indices
             * @param _vertex_indices New value to be copied in member vertex_indices
             */
            eProsima_user_DllExport void vertex_indices(
                    const shape_msgs::msg::uint32__3& _vertex_indices);

            /*!
             * @brief This function moves the value in member vertex_indices
             * @param _vertex_indices New value to be moved in member vertex_indices
             */
            eProsima_user_DllExport void vertex_indices(
                    shape_msgs::msg::uint32__3&& _vertex_indices);

            /*!
             * @brief This function returns a constant reference to member vertex_indices
             * @return Constant reference to member vertex_indices
             */
            eProsima_user_DllExport const shape_msgs::msg::uint32__3& vertex_indices() const;

            /*!
             * @brief This function returns a reference to member vertex_indices
             * @return Reference to member vertex_indices
             */
            eProsima_user_DllExport shape_msgs::msg::uint32__3& vertex_indices();

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
                    const shape_msgs::msg::MeshTriangle& data,
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

            shape_msgs::msg::uint32__3 m_vertex_indices;

        };
    } // namespace msg
} // namespace shape_msgs

#endif // _FAST_DDS_GENERATED_SHAPE_MSGS_MSG_MESHTRIANGLE_H_