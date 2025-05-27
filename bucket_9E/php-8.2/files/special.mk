_USES_extract+=         660:add-phpext-desc
_USES_stage+=		935:add-phpext-plist

EXTENSIONS=	${SUBPACKAGES:Nset:Nprimary:Ndev:Nman}
SUFFIX=		${VERSION:R:S/.//}
PHP_EXT_DIR=	20220829
PRIOR_session=	18
PRIOR_opcache=	10

CONFIGURE_ARGS+= ${EXTENSIONS:C/^/--enable-/}

add-phpext-desc:
.  for S in ${EXTENSIONS}
	@${ECHO} "This ${NAMEBASE} subpackage contains the ${S} extension." > ${_DESC_FILE}.${S}
.  endfor

add-phpext-plist:
.  for S in ${EXTENSIONS}
	@${ECHO_CMD} "lib/php${SUFFIX}/${PHP_EXT_DIR}/${S}.so" \
		>> ${WRKDIR}/.manifest.${S}.mktmp
	@${FIND} -P ${STAGEDIR}${PREFIX}/include/php${SUFFIX}/ext/${S} ! -type d 2>/dev/null | \
		${SED} -ne 's,^${STAGEDIR}${PREFIX}/,,p' \
		>> ${WRKDIR}/.manifest.${S}.mktmp
	@${ECHO_CMD} "etc/php${SUFFIX}/ext-${PRIOR_${S}:U20}-${S}.ini" \
		>> ${WRKDIR}/.manifest.${S}.mktmp

	# lua script commands
	@${SH} ${MK_SCRIPTS}/php_heredoc.sh script "${_SCRIPT_FILE}.${S}" \
		"${S}" "php${SUFFIX}"

	# message files
	@${SH} ${MK_SCRIPTS}/php_heredoc.sh message \
		"${_MESSAGE_FILE}.${S}" \
		"${S}" \
		"extension=${S}.so" \
		"${PREFIX}/etc/php${SUFFIX}/ext-${PRIOR_${S}:U20}-${S}.ini"
.  endfor
