{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, ...} @ inputs:
    inputs.utils.lib.eachDefaultSystem (system: let
      pkgs = inputs.nixpkgs.legacyPackages.${system};
      cc = pkgs.gcc12;

      deriv = name: inputs:
        pkgs.stdenv.mkDerivation {
          inherit name;
          src = ./.;

          buildInputs = [cc] ++ (with pkgs; [glibc gnumake libossp_uuid]) ++ inputs;
          makeFlags = ["CC=${cc}/bin/gcc"];
          hardeningDisable = ["format" "fortify"];
          enableParallelBuilding = true;

          buildPhase = ''
            make ${name}
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp ${name} $out/bin
          '';
        };
    in rec {
      formatter = pkgs.alejandra;

      devShells.default = pkgs.mkShell {
        packages =
          packages.server.buildInputs
          ++ (with pkgs; [
            criterion
            gcovr
            valgrind
            bear
            gdb
            libuuid
          ]);
        LD_LIBRARY_PATH = ["./libs/myteams"];
      };

      packages = {
        server = deriv "myteams_server" [];
        client = deriv "myteams_cli" [];
      };
    });
}
