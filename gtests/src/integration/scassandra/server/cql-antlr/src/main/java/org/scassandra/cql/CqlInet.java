/*
 * Copyright (C) 2016 Christopher Batey and Dogan Narinc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.scassandra.cql;

import java.net.InetAddress;

public class CqlInet extends PrimitiveType {
    CqlInet() {
        super("inet");
    }

    // comes from the server as a string
    @Override
    public boolean equals(Object expected, Object actual) {
        if (expected == null) return actual == null;
        if (actual == null) return expected == null;

        if (expected instanceof String) {
            try {
                return expected.equals(actual);
            } catch (Exception e) {
                throw throwInvalidType(expected, actual, this);
            }
        } else if (expected instanceof InetAddress) {
            return ((InetAddress) expected).getHostAddress().equals(actual);
        }

        throw throwInvalidType(expected, actual, this);
    }
}
