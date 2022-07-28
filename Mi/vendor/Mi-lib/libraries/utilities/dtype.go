package utilities

import (
	"strings"
	"strconv"
)

func ExtractDType(data string) int64 {

	dtypeStr := strings.Split(strings.Split(data, "]:")[0], "[DTYPE: ")[1]
	dtype, err := strconv.ParseInt(dtypeStr, 0, 32)
	if err == nil {
		return dtype
	}
	return 0
}