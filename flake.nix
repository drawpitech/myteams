{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, ...} @ inputs:
    inputs.utils.lib.eachDefaultSystem (system: let
      pkgs = inputs.nixpkgs.legacyPackages.${system};
      cc = pkgs.gcc12;

      deriv = name:
        pkgs.stdenv.mkDerivation rec {
          inherit name;
          src = ./.;

          buildInputs = with pkgs; [glibc gnumake pkg-config libuuid];
          nativeBuildInputs = [pkgs.makeWrapper];
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
          postFixup = ''
            wrapProgram $out/bin/${name} --set LD_LIBRARY_PATH ${./libs/myteams}
          '';
        };
    in rec {
      formatter = pkgs.alejandra;

      devShells.default = pkgs.mkShell {
        packages =
          packages.server.buildInputs
          ++ (with pkgs; [
            python312
            criterion
            gcovr
            valgrind
            bear
            gdb
          ]);
        LD_LIBRARY_PATH = ["./libs/myteams"];
      };

      packages = {
        server = deriv "myteams_server";
        client = deriv "myteams_cli";
      };
    });
}
