sudo qemu-system-aarch64 -kernel "build/app-maria_kvm-arm64" \
                         -machine virt \
                         -cpu cortex-a57 \
                         -nographic \
                         -S \
                         -s