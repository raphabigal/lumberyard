/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/VertexContainerInterface.h>

namespace Visibility
{
    // Request bus for the PortalComponent.
    class PortalRequests
    {
    public:
        virtual float GetHeight() = 0;
        virtual bool GetDisplayFilled() = 0;
        virtual bool GetAffectedBySun() = 0;
        virtual float GetViewDistRatio() = 0;
        virtual bool GetSkyOnly() = 0;
        virtual bool GetOceanIsVisible() = 0;
        virtual bool GetUseDeepness() = 0;
        virtual bool GetDoubleSide() = 0;
        virtual bool GetLightBlending() = 0;
        virtual float GetLightBlendValue() = 0;

    protected:
        ~PortalRequests() = default;
    };

    /// Type to inherit to implement PortalRequests.
    using PortalRequestBus = AZ::EBus<PortalRequests, AZ::ComponentBus>;

} // namespace Visibility
