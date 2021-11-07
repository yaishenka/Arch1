add_library(BanksLibrary SHARED accounts/IAccount.cpp accounts/TrustedAccount.cpp accounts/UntrustedAccount.cpp OperationHistory.cpp)

install(
    TARGETS BanksLibrary
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/bin
)