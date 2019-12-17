.if "${OPSYS}" == "DragonFly"
BOOTSTRAP_RUST=		1.38.0
BOOTSTRAP_CARGO=	0.39.0
DF_INDEX+=		2 3 4
COMPEXT=		zst
.elif "${OPSYS}" == "FreeBSD"
BOOTSTRAP_RUST=		1.38.0
BOOTSTRAP_CARGO=	0.39.0
DF_INDEX+=		5 6 7
COMPEXT=		gz
.elif "${OPSYS}" == "Linux"
BOOTSTRAP_RUST=		1.38.0
BOOTSTRAP_CARGO=	0.39.0
DF_INDEX+=		8 9 10
COMPEXT=		gz
SFX=			${ARCH_STANDARD}-unknown-linux-gnu
.endif
SFX?=			${ARCH_STANDARD}-unknown-${OPSYS:tl}
SRC_RUSTC?=		rustc-${BOOTSTRAP_RUST}-${SFX}
SRC_RUSTSTD?=		rust-std-${BOOTSTRAP_RUST}-${SFX}
SRC_CARGO?=		cargo-${BOOTSTRAP_CARGO}-${SFX}