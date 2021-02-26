package api

import (
	"testing"
)

func TestApi(t *testing.T) {
	body, err := Query("kanye")
	if err != nil {
		t.Error(err)
		return
	}
	defer body.Close()
}
