package api

import (
	"io"
	"fmt"
	"net/http"
	"os"
	"errors"
	"path"
)

var offline bool = false
var cacheDir string = "./.cache"

func CheckCache(query string) (ok bool, err error) {
	err = os.MkdirAll(cacheDir, 0777)
	if err != nil {
		return false, err
	}
	filePath := path.Join(cacheDir, query)
	file, err := os.Open(filePath)
	if err != nil {
		return false, err
	}
	defer file.Close()
	return true, nil
}

func StoreInCache(query string, r io.ReadCloser) (err error) {
	err = os.MkdirAll(cacheDir, 0777)
	if err != nil {
		return err
	}
	filePath := path.Join(cacheDir, query)
	file, err := os.Create(filePath)
	if err != nil {
		return err
	}
	defer file.Close()
	b := make([]byte, 1024)
	for {
		n, err := r.Read(b)
		if err != nil && err != io.EOF {
			return err
		}
		if n== 0 {
			break
		}
		if _, err := file.Write(b[:n]); err != nil {
			return err
		}
	}
	return nil

}

func Query(query string) (body io.ReadCloser, err error) {
	ok, err := CheckCache(query)
	if ok == true {
		filePath := path.Join(cacheDir, query)
		file, err := os.Open(filePath)
		if err != nil {
			return body, err
		}
		return file, nil
	}
	if offline == true {
		return body, errors.New("Request not in cache and in offline mode")
	}
	key := "AIzaSyAb_N1cD6zJ1GLwbqF2VTfrz39amyUOh7s"
	urlBase := "kgsearch.googleapis.com/v1/entities:search"
	url := fmt.Sprintf("https://%s?query=%s&key=%s", urlBase, query, key)
	resp, err := http.Get(url)
	if err != nil {
		return body, err
	}
	err = StoreInCache(query, resp.Body)
	if err != nil {
		return body, err
	}
	filePath := path.Join(cacheDir, query)
	file, err := os.Open(filePath)
	if err != nil {
		return body, err
	}
	return file, nil
}
