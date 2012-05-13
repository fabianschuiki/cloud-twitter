cmake_minimum_required (VERSION 2.6)
project (cloud-twitter)

add_executable (cloud-twitterd
	service.c
	main.c)

target_link_libraries (cloud-twitterd cloud-service)

