# Copyright (c) 2025 RealTimeChris (Chris M.)
# 
# This software is offered under a restricted-use license to a party (hereafter “the Licensee”) whose identity shall be disclosed and confirmed in writing by the Author.
# 
# The License is granted under the following terms:
# 
# 1. **Scope of Use**: The Licensee is granted an exclusive right to use this software for internal purposes only. Redistribution, 
#       sublicensing, public disclosure, or publication of this software or derivative works is prohibited without explicit written consent from the Author.
# 
# 2. **Ownership**: The Author retains full ownership of the software and all intellectual property rights.
# 
# 3. **Revocability**: The Author reserves the right to revoke this license at any time, for any reason, without compensation. Upon revocation, 
#       the Licensee must immediately cease all use of the software and destroy all copies in their possession.
# 
# 4. **Transferability**: This license is non-transferable and may not be reassigned without the Author’s written consent.
# 
# 5. **No Warranty**: The software is provided "as is", without warranty of any kind, express or implied.
# Signed,  
# RealTimeChris (Chris M.)  
# 2025

add_executable(rt-ut-main main.cpp)

target_link_libraries(rt-ut-main
    PUBLIC
        rt-ut::rt-ut
)

install(
    FILES
        $<TARGET_FILE:rt-ut-main>
    DESTINATION bin
    OPTIONAL
)
