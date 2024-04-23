FROM nixos/nix

# Setup repo
WORKDIR /poll
COPY . .

# Build server
RUN nix \
    --extra-experimental-features "nix-command flakes" \
    build .#server

CMD ./result/bin/myteams_server 6969
